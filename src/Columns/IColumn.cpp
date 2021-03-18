//#include <IO/WriteBufferFromString.h>
//#include <IO/Operators.h>
#include <sstream>
#include <Columns/IColumn.h>
//#include <Columns/ColumnNullable.h>
#include <Columns/ColumnConst.h>
//#include <Core/Field.h>


namespace DB
{

std::string IColumn::dumpStructure() const
{
    std::stringstream res;
    res << getFamilyName() << "(size = " << size();

    ColumnCallback callback = [&](ColumnPtr & subcolumn)
    {
        res << ", " << subcolumn->dumpStructure();
    };

    const_cast<IColumn*>(this)->forEachSubcolumn(callback);

    res << ")";
    return res.str();
}

void IColumn::insertFrom(const IColumn & src, size_t n)
{
    insert(src[n]);
}

//bool isColumnNullable(const IColumn & column)
//{
//    return checkColumn<ColumnNullable>(column);
//}

//bool isColumnConst(const IColumn & column)
//{
//    return checkColumn<ColumnConst>(column);
//}

}
