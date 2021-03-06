#include <alloca.h>
#include "gtest/gtest.h"
#include "vec/common/columns_hashing.h"
#include "vec/common/hash_table/hash_map.h"
#include "vec/common/hash_table/hash_set.h"

namespace doris::vectorized {

template <typename TData>
struct AggregationMethodSerialized {
    using Data = TData;
    using Key = typename Data::key_type;
    using Mapped = typename Data::mapped_type;

    Data data;

    AggregationMethodSerialized() {}

    template <typename Other>
    AggregationMethodSerialized(const Other& other) : data(other.data) {}

    using State = ColumnsHashing::HashMethodSerialized<typename Data::value_type, Mapped>;

    static const bool low_cardinality_optimization = false;

    static void insertKeyIntoColumns(const StringRef& key, MutableColumns& key_columns,
                                     const Sizes&) {
        auto pos = key.data;
        for (auto& column : key_columns) pos = column->deserializeAndInsertFromArena(pos);
    }
};

TEST(HashTableTest, hash_table_test) {
    using AggregateDataPtr = char*;
    using AggregatedDataWithStringKey = HashMapWithSavedHash<StringRef, AggregateDataPtr>;
    std::unique_ptr<AggregationMethodSerialized<AggregatedDataWithStringKey>> serialized(new AggregationMethodSerialized<AggregatedDataWithStringKey>());
    using Method = AggregationMethodSerialized<AggregatedDataWithStringKey>;
    using AggState = Method::State;

    auto column = ColumnInt32::create();
    int key = 0x3355;
    column->insertData((const char*)&key,sizeof(key));
    ColumnRawPtrs raw_ptrs = {column->getPtr().get()};
    Sizes key_sizes = {1};

    AggState state(raw_ptrs, key_sizes, nullptr);
    Arena agg_pool;
    auto emplace_result = state.emplaceKey(serialized.get()->data, 0, agg_pool);

    AggregateDataPtr aggregate_data = nullptr;
    
    if (emplace_result.isInserted()) {
        /// exception-safety - if you can not allocate memory or create states, then destructors will not be called.
        emplace_result.setMapped(nullptr);
        // alloc data for agg_data
        aggregate_data = static_cast<AggregateDataPtr>(agg_pool.alloc(4096));
        emplace_result.setMapped(aggregate_data);
    } else
        aggregate_data = emplace_result.getMapped();

    // do some agg caculate

    // get result from hash_table
    auto& method = *serialized;
    auto& data = serialized->data;

    MutableColumns key_columns;
    key_columns.emplace_back((*column->getPtr()).mutate());

    data.forEachValue([&](const auto & key, auto & mapped)
    {
        // insert keys
        method.insertKeyIntoColumns(key, key_columns, key_sizes);
        // insert values
    });

    ASSERT_EQ(key_columns[0]->getInt(0), key);

    auto iter = data.begin();
    auto end = data.end();
    while(iter!=end) {
        const auto & key = iter->getFirst();
        auto &mapped = iter->getSecond();
        method.insertKeyIntoColumns(key, key_columns, key_sizes);
        ASSERT_TRUE(mapped != nullptr);
        ++iter;
    }
}

TEST(HashSetTest, basic_test) {
    using Key = int32_t;

    /// When creating, the hash table must be small.
    using Set = HashSet<
        Key,
        HashCRC32<Key>,
        HashTableGrower<4>,
        HashTableAllocatorWithStackMemory<sizeof(Key) * (1 << 4)>>;
    Set hash_set;

    for(int i = 0;i < 1000;++i) {
        hash_set.insert(i);
    }

    for(int i = 0;i < 1000; ++i) {
        auto cell = hash_set.find(i);
        ASSERT_NE(cell, nullptr);
    }

    auto cell = hash_set.find(4096);
    ASSERT_EQ(cell, nullptr);

    std::stringstream ss;
    hash_set.write(ss);

    Set hash_set_2;
    hash_set_2.read(ss);
    ASSERT_EQ(hash_set_2.size(), 1000);

    auto cell_2 = hash_set_2.find(4096);
    ASSERT_EQ(cell_2, nullptr);

    for(int i = 0;i < 1000; ++i) {
        bool res = hash_set_2.has(i);
        ASSERT_TRUE(res);
        cell_2 = hash_set_2.find(i);
        ASSERT_NE(cell_2, nullptr);
    }

}

} // namespace doris::vectorized

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
