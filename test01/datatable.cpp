//
//  datatable.cpp
//  test01
//
//  Created by 楠本健佑 on 2014/08/24.
//  Copyright (c) 2014年 楠本健佑. All rights reserved.
//

#include <cassert>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "datatable.h"


DataTable::DataTable ()
: m_defaultDelimiter (",")
{
    m_dataTable.clear ();
}

bool
DataTable::ReadCsv (std::string s_filename, std::string s_delimiter)
{
    std::ifstream ifs(s_filename.c_str(), std::ios::in);
    
    if (!ifs) return false;
    
    m_dataTable.clear ();
    std::string s_temp;
    std::vector<std::string> v_temp;
    
    if (s_delimiter == "") s_delimiter = m_defaultDelimiter;
    
    for (unsigned int line = 0; getline (ifs, s_temp); line++) {
        m_dataTable.push_back (v_temp);
        m_dataTable[line].push_back (s_temp);
        
        unsigned int col = 0;
        
        while (1) {
            std::string::size_type pos = m_dataTable[line][col].find (s_delimiter, 0);
            if (pos == std::string::npos) break;
            m_dataTable[line].push_back (s_temp);
            m_dataTable[line][col] = m_dataTable[line][col].substr (0, pos);
            m_dataTable[line][col+1] = m_dataTable[line][col+1].substr (pos+1);
            col++;
        }
    }
    
    return true;
}

bool
DataTable::WriteCsv (std::string s_filename, std::string s_delimiter)
{
    //std::ofstream ofs(s_filename.c_str(), std::ios::out | std::ios::app);
    std::ofstream ofs(s_filename.c_str(), std::ios::out);
    
    if (!ofs) return false;
    
    if (s_delimiter == "") s_delimiter = m_defaultDelimiter;
    
    for (std::vector< std::vector<std::string> >::iterator rowItr = m_dataTable.begin ();
         rowItr != m_dataTable.end (); rowItr++) {
        for (std::vector<std::string>::iterator elmItr = rowItr->begin (); elmItr != rowItr->end (); elmItr++) {
            ofs << *elmItr;
            if ((elmItr + 1) != rowItr->end ()) {
                ofs << s_delimiter;
            }
        }
        ofs << std::endl;
    }
    
    return true;
}

void
DataTable::InsertRow (std::vector<std::string> newRow, int pos)
{
    if (pos < 1) return;
    
    int i = 1;
    
    for (std::vector< std::vector<std::string> >::iterator rowItr = m_dataTable.begin (); ; rowItr++) {
        if (pos == i) {
            if (rowItr == m_dataTable.end ())
                m_dataTable.push_back (newRow);
            else
                m_dataTable.insert (rowItr, newRow);
            return;
        }
        
        if (rowItr == m_dataTable.end ()) {
            std::vector<std::string> temp;
            m_dataTable.push_back (temp);
            rowItr = m_dataTable.end ();
            rowItr--;
        }
        i++;
    }
}

void
DataTable::InsertCol (std::vector<std::string> newCol, int pos)
{
    if (pos < 1) return;
    if (newCol.empty()) return;
    
    std::vector<std::string>::const_iterator newColItr = newCol.begin ();
    
    for (std::vector< std::vector<std::string> >::iterator rowItr = m_dataTable.begin (); ; rowItr++) {
        if (rowItr == m_dataTable.end ()) {
            std::vector<std::string> temp;
            m_dataTable.push_back (temp);
            rowItr = m_dataTable.end ();
            rowItr--;
        }
        int i = 1;
        for (std::vector<std::string>::iterator elmItr = rowItr->begin (); ; elmItr++) {
            if (i == pos) {
                if (elmItr == rowItr->end ())
                    rowItr->push_back(*newColItr);
                else
                    rowItr->insert(elmItr, *newColItr);
                newColItr++;
                break;
            }
            if (elmItr == rowItr->end ()) {
                std::string temp;
                rowItr->push_back (temp);
                elmItr = rowItr->end ();
                elmItr--;
            }
            i++;
        }
        if (newColItr == newCol.end ()) return;
    }
}

void
DataTable::PushBackRow (std::vector<std::string> newRow)
{
    InsertRow (newRow, static_cast<int>(m_dataTable.size ()) + 1);
}

std::string
DataTable::GetData (int row, int col)
{
    return m_dataTable.at(row-1).at(col-1);
}

std::vector<std::string>
DataTable::GetRow (int row)
{
    return m_dataTable.at(row-1);
}

DataTable
DataTable::GetRows (std::vector<int> order)
{
    DataTable result;
    
    for (std::vector<int>::const_iterator itr = order.begin (); itr != order.end (); itr++) {
        result.PushBackRow (GetRow (*itr));
    }
    
    return result;
}

std::vector<std::string>
DataTable::GetCol (int col)
{
    std::vector<std::string> collum;
    col--;
    
    for (std::vector< std::vector<std::string> >::iterator rowItr = m_dataTable.begin ();
         rowItr != m_dataTable.end (); rowItr++) {
        int i = 0;
        for (std::vector<std::string>::iterator elmItr = rowItr->begin (); elmItr != rowItr->end (); elmItr++, i++) {
            if (i == col) {
                collum.push_back (*elmItr);
            }
        }
    }
    return collum;
}

bool
DataTable::IsEmpty ()
{
    if (m_dataTable.empty ()) return true;
    if (m_dataTable[0].empty ()) return true;
    return false;
}

std::vector<int>
DataTable::Find (std::string s_search, int i_order)
{
    std::vector<int> result;
    
    if (i_order != data_type::row && i_order != data_type::col) return result;
    
    int row = 1, col;
    
    for (std::vector< std::vector<std::string> >::iterator rowItr = m_dataTable.begin ();
         rowItr != m_dataTable.end (); rowItr++) {
        col = 1;
        for (std::vector<std::string>::iterator elmItr = rowItr->begin (); elmItr != rowItr->end (); elmItr++) {
            if (*elmItr == s_search) {
                if (i_order == data_type::row) result.push_back (row);
                if (i_order == data_type::col) result.push_back (col);
            }
            col++;
        }
        row++;
    }
    
    return result;
}

void
DataTable::SetDefaultDelimiter (std::string s_delimiter)
{
    m_defaultDelimiter = s_delimiter;
}

void
DataTable::PrintDataTable ()
{
    for (std::vector< std::vector<std::string> >::iterator rowItr = m_dataTable.begin ();
         rowItr != m_dataTable.end (); rowItr++) {
        for (std::vector<std::string>::iterator elmItr = rowItr->begin (); elmItr != rowItr->end (); elmItr++) {
            std::cout << *elmItr;
            if ((elmItr + 1) != rowItr->end ()) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
}

template<typename T>
T StringToBinary (const std::string& text, int base) {
    assert (base == 8 || base == 10 || base == 16);
    std::istringstream is (text);
    T value;
    switch (base) {
        case 8:
            is >> std::oct >> value;
            break;
        case 10:
            is >> value;
            break;
        case 16:
            is >> std::hex >> value;
            break;
        default:
            ;
    }
    
    return value;
}

template<typename T>
std::string BinaryToString (T value, int base) {
    assert (base == 8 || base == 10 || base == 16);
    std::ostringstream os;
    switch (base) {
        case 8:
            if (value < 0) {
                os << '-';
                value *= -1;
            }
            os << std::oct;
            break;
        case 10:
            os << std::dec;
            break;
        case 16:
            if (value < 0) {
                os << '-';
                value *= -1;
            }
            os << std::hex;
            break;
    }
    os << value;
    return os.str();
}

