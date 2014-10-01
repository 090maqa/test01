//
//  main.cpp
//  test01
//
//  Created by 楠本健佑 on 2014/08/24.
//  Copyright (c) 2014年 楠本健佑. All rights reserved.
//

#include <cassert>
#include <fstream>
#include <iostream>


#include "datatable.h"
#include "mylibrary.h"


/******************** main ********************/

int main (void)
{
    PrintCurrentDirectory();
    
    DataTable combat_log;
    
    if (!combat_log.ReadCsv("data/海戦・ドロップ報告書.csv")) {
        std::cout << "File cannot open." << std::endl;
        return 1;
    }
    
    //combat_log.PrintDataTable();
    printf("sub!!!!!!!!!!!");
    
    return 0;
}

