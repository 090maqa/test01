//
//  datatable.h
//  test01
//
//  Created by 楠本健佑 on 2014/08/24.
//  Copyright (c) 2014年 楠本健佑. All rights reserved.
//

#ifndef test01_datatable_h
#define test01_datatable_h

// std::stringクラスの前方宣言は、typedefの関係上煩雑。
// なので、応急処置的にstringをincludeする。
#include <string>
// std::vectorテンプレートクラスの前方宣言は、通常は
//   namespace std { template<typename T> class vector; }
// とすると可能であるが、今回は入れ子のvectorがあり難しい。
#include <vector>


class DataTable
{
public:
    DataTable ();
    
    // 第一引数で指定されたcsvファイルのデータを読み込む。
    // 第二引数はファイルの区切り文字を指定する。指定無しの場合、デフォルトの区切り文字（,）が使用される。
    // ファイルのオープンに失敗した場合falseを返す。
    bool ReadCsv (std::string,std::string = "");
    
    // 現在格納されているデータを第一引数で指定されたファイルにcsv形式で書き込む。
    // 第二引数には使用する区切り文字を指定する。指定無しの場合、デフォルトの区切り文字（,）が使用される。
    // ファイルのオープンに失敗した場合falseを返す。
    bool WriteCsv (std::string,std::string = "");
    
    // 第一引数で渡されたリストを第二引数で指定された行に挿入する。
    void InsertRow   (std::vector<std::string>,int);
    // 第一引数で渡されたリストを第二引数で指定された列に挿入する。
    void InsertCol   (std::vector<std::string>,int);
    // 第一引数で渡されたリストをデータの最後の行に挿入する。
    void PushBackRow (std::vector<std::string>);
    // 第一引数で渡されたリストをデータの最後の列に挿入する。
    //void PushBackCol (std::vector<std::string>);
    
    // 第一引数：行、第二引数：列で指定された箇所のデータを返す。
    // 指定された箇所がデータの範囲外であった場合out_of_range例外を投げる。
    std::string              GetData (int,int);
    // 第一引数で指定された行、またはリストで指定された行を格納したDataTableを返す。
    // 指定された箇所がデータの範囲外であった場合out_of_range例外を投げる。
    std::vector<std::string> GetRow  (int);
    DataTable                GetRows (std::vector<int>);
    // 第一引数で指定された列を返す。
    // 指定された箇所がデータの範囲外であった場合空のリストを返す。
    // 各行の大きさがまちまちになっているようなデータの場合は、期待した動作がなされないかもしれない。
    std::vector<std::string> GetCol (int);
    
    // クラスにデータが何も格納されていない場合trueを返す。
    bool IsEmpty ();
    
    // 第一引数で指定された文字列と一致する要素を持つ行番号または列番号のリストを返す。
    // 第二引数で返すリストの種類を選択できる。（行:data_type::row、列：data_type::col）
    // 第二引数に何も指定しなければ、行番号が選択される。
    std::vector<int> Find (std::string,int = data_type::row);
    
    // デフォルトの区切り文字を変更する。
    void SetDefaultDelimiter (std::string);
    
    // 格納されているデータを標準出力に出力する。
    virtual void PrintDataTable ();
    
    struct data_type {
        static const int row = 1;
        static const int col = 2;
    };
    
private:
    std::vector< std::vector<std::string> >  m_dataTable;
    std::string m_defaultDelimiter;
};

// 第一引数で渡された文字列を、第二引数で指定された進数で数値に変換する。
template<typename T> T StringToBinary (const std::string &, int = 10);
// 第一引数で渡された数値を、第二引数で指定された進数で文字列に変換する。
template<typename T> std::string BinaryToString (T, int = 10);


#endif
