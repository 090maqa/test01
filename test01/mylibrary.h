//
//  mylibrary.h
//  test01
//
//  Created by 楠本健佑 on 2014/08/24.
//  Copyright (c) 2014年 楠本健佑. All rights reserved.
//

#ifndef test01_mylibrary_h
#define test01_mylibrary_h

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

inline void
PrintCurrentDirectory ()
{
    char *cwd ;
    cwd=getcwd(NULL, 0);
    printf("CWD:%s\n", cwd);
    free(cwd);
}

#endif
