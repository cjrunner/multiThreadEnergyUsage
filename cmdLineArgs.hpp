//
//  cmdLineArgs.hpp
//  multiThreadEnergyUsage
//
//  Created by Clifford Campo on 6/5/18.
//  Copyright © 2018 CliffordCampo. All rights reserved.
//

#ifndef cmdLineArgs_hpp
#define cmdLineArgs_hpp

#include <stdio.h>
#include <iostream>
class CmdLineArgs {
private:
public:
    const char *_clDatabaseName;
    const char *_results_File ;
    const char *_clUserID;
    const char *_clPW;
    const char *_clHostID;
    const char *_clPortID;
    const char *_clSQL;
    bool _debug1 = false;
    bool _debug2 = false;
    bool _debug3 = false;
    bool _useKelvin = false;

CmdLineArgs();
~CmdLineArgs();
};
#endif /* cmdLineArgs_hpp */

