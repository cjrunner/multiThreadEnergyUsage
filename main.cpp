//
//  main.cpp
//  energyUsage (based on c++Postgres)
//
//  Created by Clifford Campo on 4/24/18.
//  Copyright © 2018 CliffordCampo. All rights reserved.
//

#include <AvailabilityMacros.h>
#include <iostream>
#include <thread>
#include "/usr/local/pgsql/pgsql101/include/libpq-fe.h"
#include <cstring>
#include <sstream>
#include <getopt.h>
#include "cmdLIneArgs.hpp"
#include "makeHelpMessage.hpp"
#include "baseClass.hpp" 
#include "effectConnection.hpp"
#include "myPrototypes.hpp"
#include "alignField.hpp"
//#include "getMCS.hpp"
using namespace std;
extern const short numberOfRowsInMotherOFAllSelectStatements;
extern const short numberOfColumnsInMotherOFAllSelectStatements;
extern char *defalutResultsFileName[];
extern char *defaultDependentVariableColumn;
extern const char *const message;
extern const char *motherOfAllSelectStatements[];
extern const char *help_Message_Array[];
extern const int numberOfEntries;
extern const char *cases[];
extern const char *dependentVariableColumn[];
void initializeBaseClass (BaseClass *, BaseClass *);
int selectFromTable(BaseClass *, int);

int main(int argc, char* argv[])  {
    
    int (*ptf[3])(BaseClass *, int);
    CmdLineArgs *ptrCLA = new CmdLineArgs;
    char connectionString[MAXBUFSIZE];
    char *ptrConnectionStringBuffer = connectionString;
    cout << __TIMESTAMP__ << "\tLine " <<  __LINE__ <<"\tFile " << __FILE__ << "\nBeginning execution of program:\n" << *(argv+0) << std::endl;
    const struct option longopts[] =
    {
        {"dbname",    required_argument, 0, 'D'},
        {"help",       no_argument,        0, 'h'},
        {"userid",    required_argument, 0, 'U'},
        {"hostid",    required_argument, 0, 'H'},
        {"port",       required_argument, 0, 'P'},
        {"sql",         required_argument, 0, 'S'},
        {"kelvin",      no_argument,        0, 'k'},
        {"resultsFile", required_argument, 0, 'f'},
        {"debug1",     no_argument,         0, '1'},
        {"debug2",     no_argument,         0, '2'},
        {"debug3",     no_argument,         0, '3'},
        {0,0,0,0}, //End of array
    };
    const char *const commandLineSwitches = "123hkD:U:P:H:S:f:";
    int index;

    
    
    int numberOfMessageSegments = 0;
    while ( *(help_Message_Array + numberOfMessageSegments)  )  {numberOfMessageSegments++;} //Loop until we hit the pointer that points to location 0x'00 00 00 00 00 00 00 00', marking the end of the array.
    numberOfMessageSegments--; //Back-off 1 becaue the very last entry in the array, that gets counted, is an all zero terminator, but we want our count to indicate the number of valid addresses that point to strings.
    
    char  iarg= NULL; //Jumping though hoops just to make iarg to appear as a character in the debugger.
    //Each thread should get its own copy of BaseClass
//    BaseClass *bc = new BaseClass( );  /* << =============== bc ================= */


    //turn off getopt error message
    opterr=1;
    MakeHelpMessage *MSG = new MakeHelpMessage( (*(argv +0) ),  &help_Message_Array[0], numberOfMessageSegments  );     /* << =============== MSG ================ */
    while( (iarg = (char)getopt_long(argc, argv, commandLineSwitches, longopts, &index)) != -1) {  //Jumping though hoops just to make iarg to appear as a character in the debugger.
        if (iarg < ZERO) break;
        switch (iarg)
        {
            case 'D': //Database Name
                ptrCLA->_clDatabaseName = optarg;
                std::cout << "Database Name: " << ptrCLA->_clDatabaseName << std::endl;
                break;
            case 'f': //resultsFile
                std::cout << "resultsFile: " << optarg << std::endl;
                ptrCLA->_results_File = optarg;
                break;
            case 'k': //Use kelvin temperatures as independent variable
                ptrCLA->_useKelvin = true;
                break;
            case 'U': //Userid
                ptrCLA->_clUserID = optarg;
                std::cout << "User ID: " << ptrCLA->_clUserID << std::endl;
                break;


                
            case 'H': //Hostid
                ptrCLA->_clHostID = optarg;
               std::cout << "HostID: " << ptrCLA->_clHostID << std::endl;
                break;
                
            case 'P':   //Port
                ptrCLA->_clPortID = optarg;
                std::cout << "PortID: " << ptrCLA->_clPortID << std::endl;
                break;
            case 'S':  //SQL
                ptrCLA->_clSQL = optarg;
                std::cout << "SELECT SQL STATEMENT looks like: " << ptrCLA->_clSQL << std::endl;
                break;
            case '1':  //Debug stage 1
                ptrCLA->_debug1=true;
                break;
            case '2': //Debug stage 2
                ptrCLA->_debug2=true;
                break;
            case '3': //Debug stage 3
                ptrCLA->_debug3=true;
                break;
            case 'h': //Help
                
                std::cout << MSG->createMessage(*(argv +0) )  << std::endl;
                MSG->~MakeHelpMessage(); //Call destructor to delete dynamically acquired storage.
                exit (WONDERFUL);

            default:
                std::cerr << "Unknown command line parameter. Skipping." << std::endl;
                break;
        } //End of switch
    }  //End of While
//EffectConnection(char *usersConnectStringBuffer, const char *host="127.0.0.1", const char *user="cjc", const char *database="LocalWeather", const char *port="5436", const char *file="/Users/cjc/.pgpass");
    EffectConnection *ecs = new EffectConnection(ptrConnectionStringBuffer, ptrCLA->_clHostID, ptrCLA->_clUserID, ptrCLA->_clDatabaseName, ptrCLA->_clPortID  );
    if (ptrCLA->_debug1) std::cout << "Connection String Looks Like: " << connectionString << std::endl;
    int rc=WONDERFUL;
    std::stringstream outstring = stringstream();
    
    //    PGconn *conn = ecs->connectToDataBase(ptrConnectionStringBuffer);  /* << =================================== */
    BaseClass *ptrbc1 = new BaseClass( ptrCLA, M1KWH);
    ptrbc1->debugFlags.mycase = M1KWH;
    ptrbc1->setConString(ptrConnectionStringBuffer);
    ptrbc1->lookAtMyConnectionString = ptrConnectionStringBuffer;
    ptrbc1->BFS = *(motherOfAllSelectStatements + M1KWHCASE );
    ptrbc1->results_File = defalutResultsFileName[M1KWHCASE];
    ptrbc1->debugFlags.intMyCase = M1KWHCASE;
    ptrbc1->debugFlags.debug2 = ptrCLA->_debug2;
    ptrbc1->debugFlags.debug3 = ptrCLA->_debug3;
    std::stringstream os1;
    ptrbc1->outstring = &os1;
    
//Let's make another clone of the original base class, bc, calling this instance bc2
    BaseClass *ptrbc2 = new BaseClass( ptrCLA, M2KWH);
    ptrbc2->setConString(ptrConnectionStringBuffer);
    ptrbc2->lookAtMyConnectionString = ptrConnectionStringBuffer;
    ptrbc2->debugFlags.mycase = M2KWH;
    ptrbc2->debugFlags.intMyCase = M2KWHCASE;
    ptrbc2->debugFlags.debug2 = ptrCLA->_debug2;
    ptrbc2->debugFlags.debug3 = ptrCLA->_debug3;
    ptrbc2->BFS = *(motherOfAllSelectStatements + M2KWHCASE );
    ptrbc2->results_File = defalutResultsFileName[M2KWHCASE];

    std::stringstream os2;
    ptrbc2->outstring = &os2;
    
//Let's make still another clone of the original base class, bc, calling this instance bc2
    
    BaseClass *ptrbc0 = new BaseClass( ptrCLA, M1M2KWH);
    ptrbc0->setConString(ptrConnectionStringBuffer);
    ptrbc0->lookAtMyConnectionString = ptrConnectionStringBuffer;
    ptrbc0->BFS = *(motherOfAllSelectStatements + M1M2KWHCASE );
    ptrbc0->results_File = defalutResultsFileName[M1M2KWHCASE];
    ptrbc0->debugFlags.intMyCase = M1M2KWHCASE;
    ptrbc0->debugFlags.debug2 = ptrCLA->_debug2;
    ptrbc0->debugFlags.debug3 = ptrCLA->_debug3;
    std::stringstream os0;
    ptrbc0->outstring = &os0;
    
//Now, let's try to spawn-off our thread and then we'll wait for it to complete
//    std::thread t1(selectFromTable, bc1, motherOfAllSelectStatements[M1KWHCASE]); //See myPrototypes.hpp for the definition of M1M2KWHCASE, M1KWHCASE, and M2KWHCASE.
//    t1.join(); //Wait for thread, t1, to end
//Using the pointer to function technique. First get the address of the function selectFromTable.
    ptf[M1M2KWHCASE] = selectFromTable;
    ptf[M1KWHCASE] = selectFromTable;
    ptf[M2KWHCASE] = selectFromTable;

    rc = (*ptf[M2KWHCASE])(ptrbc0, M2KWHCASE);
    if (rc) cerr << "The M2KWHCASE ended with a rc of " << rc << endl;
    rc = (*ptf[M1KWHCASE])(ptrbc1, M1KWHCASE);
    if (rc) cerr << "The M1KWHCASE ended with a rc of " << rc << endl;
    rc = (*ptf[M1M2KWHCASE])(ptrbc2, M1M2KWHCASE);
    if (rc) cerr << "The M1M2KWHCASE ended with a rc of " << rc << endl;

    
//Delete the objects we created.
    if (ecs != nullptr)  {
        //        ecs ->~EffectConnection();
        delete ecs ;  //2018-06-04T09:20:48 We die here, probably becaue we already deleted ecs. This delete seems to call BaseClass Destructor. So, let's remove this instruction.
        ecs = NULL;
    }
    if (ptrbc0 != nullptr)  {
 //       ptrbc0 ->~BaseClass();
        delete ptrbc0 ;  //2018-06-04T09:20:48 We die here, probably becaue we already deleted ptrbc0. This delete seems to call BaseClass Destructor. So, let's remove this instruction.
        ptrbc0=NULL;
    }
    if (ptrbc2 != nullptr)  {
//        ptrbc2 ->~BaseClass();
        delete ptrbc2 ;  //2018-06-04T09:20:48 We die here, probably becaue we already deleted ptrbc2. This delete seems to call BaseClass Destructor. So, let's remove this instruction.
        ptrbc2 = NULL;
    }
    if (ptrbc1 != nullptr)  {
//        ptrbc1 ->~BaseClass();
        delete ptrbc1 ;  //2018-06-04T09:20:48 We die here, probably becaue we already deleted ptrbc1. This delete seems to call BaseClass Destructor. So, let's remove this instruction.
        ptrbc1 = NULL;
    }


    delete ptrCLA;
    return rc;

}

