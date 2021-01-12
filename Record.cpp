#include "Record.h"

Column::Column(const std::any& value) : m_value(value)
{
}

Column::Column()
{
    m_type = Type::Null;
}

std::any& Column::getValue()
{
    return m_value;
}

void Column::setValue(const std::any& value)
{
    m_value = value;
}

Column::Type Column::getType() const
{
    return m_type;
}

void Column::setType(Type type)
{
    m_type = type;
}

std::string Column::getName() const
{
    return m_name;
}

void Column::setName(const std::string& name)
{
    m_name = name;
}

Column Record::getColumn(int index) const
{
    if (!checkIndex(index))
        return {};

    return m_columns[index];
}

int Record::getColumnCount() const
{
    return m_columns.size();
}

void Record::appendColumn(const Column& column)
{
    m_columns.push_back(column);
}

void Record::appendColumn(const std::any& value)
{
    m_columns.emplace_back(value);
}

void Record::setColumn(int index, const Column& value)
{
    if (!checkIndex(index))
        return;

    m_columns[index] = value;
}

void Record::setColumn(int index, const std::any& value)
{
    setColumn(index, Column(value));
}

bool Record::checkIndex(int index) const
{
    if ((index < 0) || (index >= m_columns.size()))
        return false;

    return true;
}
