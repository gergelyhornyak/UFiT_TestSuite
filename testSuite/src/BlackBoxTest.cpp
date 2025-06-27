#include "testSuiteHeader.hpp"

TEST(TestUFiTCommandLine, TestStepSize) {

    int testCasesSize = 11;
    std::string *commands = new std::string[testCasesSize];
    int *exitCodes = new int[testCasesSize];
    float *stepSizeInputs_num = new float[testCasesSize]{0.005f,0.05f,0.5f,5.0f,0.0f,-0.0f,-0.005f,FLT_MAX,-1*FLT_MAX,FLT_MIN,-1*FLT_MIN};
    int *expectedExitCodes = new int[testCasesSize]{0,0,0,0,0,1,0,0,0,0};

    for(int i=0; i<testCasesSize; i++)
    {
        commands[i] = commandAssembler(stepSizeInputs_num[i],5000,4,true,false,false,false,true,true,true,true,false,false,1);
        exitCodes[i] = std::system(commands[i].c_str());
        printf("%d. TEST NAME\n",i+1);
        printf("CMD: %s\n",commands[i].c_str());
        EXPECT_EQ(exitCodes[i], expectedExitCodes[i]) << "Program did not execute successfully, exit code: " << exitCodes[i] << "\n";
    }
}

TEST(TestUFiTCommandLine, TestMaxSteps) {

    int testCasesSize = 8;
    std::string *commands = new std::string[testCasesSize];
    int *exitCodes = new int[testCasesSize];
    int *maxStepInputs_num = new int[testCasesSize]{5000,-5000,0,-0,INT32_MAX,INT32_MIN,-1*INT32_MAX,-1*INT32_MIN};
    int *expectedExitCodes = new int[testCasesSize]{0,1,0,1,0,0,0,0};

    for(int i=0; i<testCasesSize; i++)
    {
        commands[i] = commandAssembler(0.005f,maxStepInputs_num[i],4,true,false,false,false,true,true,true,true,false,false,1);
        exitCodes[i] = std::system(commands[i].c_str());
        printf("%d. TEST NAME\n",i+1);
        printf("CMD: %s\n",commands[i].c_str());
        EXPECT_EQ(exitCodes[i], expectedExitCodes[i]) << "Program did not execute successfully, exit code: " << exitCodes[i] << "\n";
    }
}

TEST(TestUFiTCommandLine, TestGeometry) {

    int testCasesSize = 13;
    std::string *commands = new std::string[testCasesSize];
    int *exitCodes = new int[testCasesSize];
    int *geometryInputs_num = new int[testCasesSize]{0,1,2,3,4,5,-1,-2,-3,INT32_MAX,INT32_MIN,-1*INT32_MAX,-1*INT32_MIN};
    int *expectedExitCodes = new int[testCasesSize]{ 0,0,0,1,1,1, 1, 1, 1, 1,1,1,1};

    for(int i=0; i<testCasesSize; i++)
    {
        commands[i] = commandAssembler(0.005f,5000,4,true,false,false,false,true,true,true,true,false,false,geometryInputs_num[i]);
        exitCodes[i] = std::system(commands[i].c_str());
        printf("%d. TEST NAME\n",i+1);
        printf("CMD: %s\n",commands[i].c_str());
        EXPECT_EQ(exitCodes[i], expectedExitCodes[i]) << "Program did not execute successfully, exit code: " << exitCodes[i] << "\n";
    }
}

TEST(TestUFiTCommandLine, TestPeriodicPhi) {

    std::string commandTrue = commandAssembler(0.005f,5000,4,true,false,false,false,true,true,true,true,false,false,0);
    int exitCodesTrue = std::system(commandTrue.c_str());
    int expectedExitCodesTrue = 0;
    printf("TEST NAME\n");
    printf("CMD: %s\n",commandTrue.c_str());
    EXPECT_EQ(exitCodesTrue, expectedExitCodesTrue) << "Program did not execute successfully, exit code: " << exitCodesTrue << "\n";

    std::string commandFalse = commandAssembler(0.005f,5000,4,false,false,false,false,true,true,true,true,false,false,0);
    int exitCodesFalse = std::system(commandFalse.c_str());
    int expectedExitCodesFalse = 0;
    printf("TEST NAME\n");
    printf("CMD: %s\n",commandFalse.c_str());
    EXPECT_EQ(exitCodesFalse, expectedExitCodesFalse) << "Program did not execute successfully, exit code: " << exitCodesFalse << "\n";

}

