#include <alloca.h>
#include "gtest/gtest.h"
#include "vec/common/columns_hashing.h"
#include "vec/common/hash_table/hash_map.h"

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
} // namespace doris::vectorized

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
