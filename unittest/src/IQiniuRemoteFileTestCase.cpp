/******************************************************************************* 
 *  @file      IQiniuRemoteFileTestCase.cpp 2013\11\22 10:58:11 $
 *  @author    Wang Xiaotao<wangxiaotao1980@gmail.com> (���ı������)
 ******************************************************************************/
#include "gtest/gtest.h"
#include "Qiniu/Qiniu.h"
#include "UploadCallBack.h"


#include <iostream>
#include <fstream>

// ���Է���IQiniuRemoteFile::uploadFile()
// �ϴ��ļ��ļ�
TEST(IQiniuRemoteFileTest, TestCase0_uploadFile)
{
    std::ofstream myfile (".\\test.file");
    if (myfile.is_open())
    {
        myfile << "This is a line.\n";
        myfile << "This is another line.\n";
        for (int i = 0; i < 100000; ++i)
        {
            myfile << i ;
        }
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open file";
    }

    QINIU_NAMESPACE::QiniuUtils::Initialize();

    QINIU_NAMESPACE::QiniuToken token;

    token.m_access_key = "og9UTrj8I83ndelDQrzlpjXS8HwtiQVMV2S_v7D1";
    token.m_secret_key = "oGUsG0nvsCcltrlkci08qY48DaM-uC7MQjsWRPe0";

    QINIU_NAMESPACE::QiniuPutPolicy  putPolicy;
    QINIU_NAMESPACE::QiniuIoPutExtra ioPutExtra;


    QINIU_NAMESPACE::IQiniuUploadFile* qiniuInterface = QINIU_NAMESPACE::QiniuFactory::CreateIQiniuUploadFileObj();


    putPolicy.m_bucketName = "testqiniucppsdk";
    putPolicy.m_keyName    = "a.txt";  //2 | 614

    const char* plocalFile = ".\\test.file";
    std::string resultStr;
    QINIU_NAMESPACE::QiniuCode code = qiniuInterface->uploadFile(token, putPolicy, ioPutExtra, true, plocalFile, NULL, resultStr);

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    QINIU_NAMESPACE::QiniuFactory::DestoryIQiniuUploadFileObj(qiniuInterface);
    QINIU_NAMESPACE::QiniuUtils::Terminate();
}

// ���Է���IQiniuRemoteFile::uploadFileByChunk()
// �ֿ��ϴ��ļ��ļ�
TEST(IQiniuRemoteFileTest, TestCase0_uploadFileByChunk)
{

    std::ofstream myfile (".\\test.file");
    if (myfile.is_open())
    {
        myfile << "This is a line.\n";
        myfile << "This is another line.\n";
        for (int i = 0; i < 10000; ++i)
        {
            std::string a(1000, 'b');
            myfile << a;
        }
        myfile.close();
    }
    else
    {
        std::cout << "Unable to open file";
    }

    QINIU_NAMESPACE::QiniuUtils::Initialize();
    QINIU_NAMESPACE::QiniuToken token;

    token.m_access_key = "og9UTrj8I83ndelDQrzlpjXS8HwtiQVMV2S_v7D1";
    token.m_secret_key = "oGUsG0nvsCcltrlkci08qY48DaM-uC7MQjsWRPe0";

    QINIU_NAMESPACE::QiniuPutPolicy  putPolicy;
    QINIU_NAMESPACE::QiniuIoPutExtra ioPutExtra;


    QINIU_NAMESPACE::IQiniuUploadFile* qiniuInterface = QINIU_NAMESPACE::QiniuFactory::CreateIQiniuUploadFileObj();


    putPolicy.m_bucketName = "testqiniucppsdk";
    putPolicy.m_keyName    = "b.test";  //2 | 614

    const char* plocalFile = ".\\test.file";
    std::string resultStr;                                      
    QINIU_NAMESPACE::QiniuCode code = qiniuInterface->uploadFileByChunk(token, putPolicy, ioPutExtra, true, plocalFile, NULL, resultStr);

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    QINIU_NAMESPACE::QiniuFactory::DestoryIQiniuUploadFileObj(qiniuInterface);
    QINIU_NAMESPACE::QiniuUtils::Terminate();
}




// ���Է���IQiniuRemoteFile::getRemoteFileInfo()
// �õ�Զ���ļ�����Ϣ��
TEST(IQiniuRemoteFileTest, TestCase0_getRemoteFileInfo)
{

    QINIU_NAMESPACE::QiniuUtils::Initialize();


    QINIU_NAMESPACE::QiniuToken token;
    token.m_access_key = "og9UTrj8I83ndelDQrzlpjXS8HwtiQVMV2S_v7D1";
    token.m_secret_key = "oGUsG0nvsCcltrlkci08qY48DaM-uC7MQjsWRPe0";


    QINIU_NAMESPACE::IQiniuRemoteFile* qiniuInterface = QINIU_NAMESPACE::QiniuFactory::CreateIQiniuRemoteFileObj();

    std::string resultStr;
    
    QINIU_NAMESPACE::QiniuCode code 
        = qiniuInterface->getRemoteFileInfo(token, "testqiniucppsdk", "a.txt",resultStr);

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
                             << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    QINIU_NAMESPACE::QiniuFactory::DestoryIQiniuRemoteFileObj(qiniuInterface);

    QINIU_NAMESPACE::QiniuUtils::Terminate();

}


// ���Է���IQiniuRemoteFile::getRemoteFileInfo()
// �õ�Զ���ļ���Ϣʧ��
TEST(IQiniuRemoteFileTest, TestCase1_getRemoteFileInfo)
{

    QINIU_NAMESPACE::QiniuUtils::Initialize();

    QINIU_NAMESPACE::QiniuToken token;

    token.m_access_key = "og9UTrj8I83ndelDQrzlpjXS8HwtiQVMV2S_v7D1";
    token.m_secret_key = "oGUsG0nvsCcltrlkci08qY48DaM-uC7MQjsWRPe0";


    QINIU_NAMESPACE::IQiniuRemoteFile* qiniuInterface = QINIU_NAMESPACE::QiniuFactory::CreateIQiniuRemoteFileObj();

    std::string resultStr;

    QINIU_NAMESPACE::QiniuCode code 
        = qiniuInterface->getRemoteFileInfo(token, "testqiniucppsdk", "noExistThisFile.txt",resultStr);

    GTEST_ASSERT_EQ((code << 16 >> 16), 612)  << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    QINIU_NAMESPACE::QiniuFactory::DestoryIQiniuRemoteFileObj(qiniuInterface);

    QINIU_NAMESPACE::QiniuUtils::Terminate();

}



// ���Է���IQiniuRemoteFile::ListAllFileNames()
// �õ�����Զ���ļ�����Ϣ��
TEST(IQiniuRemoteFileTest, TestCase0_ListAllFileNames)
{

    QINIU_NAMESPACE::QiniuUtils::Initialize();

    QINIU_NAMESPACE::QiniuToken token;

    token.m_access_key = "og9UTrj8I83ndelDQrzlpjXS8HwtiQVMV2S_v7D1";
    token.m_secret_key = "oGUsG0nvsCcltrlkci08qY48DaM-uC7MQjsWRPe0";


    QINIU_NAMESPACE::IQiniuRemoteFile* qiniuInterface = QINIU_NAMESPACE::QiniuFactory::CreateIQiniuRemoteFileObj();

    std::string resultStr;
    std::string perfix;


    QINIU_NAMESPACE::QiniuCode code 
        = qiniuInterface->ListAllFileNames(token, "testqiniucppsdk", perfix.c_str(), resultStr);

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    QINIU_NAMESPACE::QiniuFactory::DestoryIQiniuRemoteFileObj(qiniuInterface);
    QINIU_NAMESPACE::QiniuUtils::Terminate();

}

// ���Է���IQiniuRemoteFile::moveRemoteFile()
// �ƶ�/�����ļ�����
TEST(IQiniuRemoteFileTest, TestCase0_moveRemoteFile)
{

    QINIU_NAMESPACE::QiniuUtils::Initialize();

    QINIU_NAMESPACE::QiniuToken token;

    token.m_access_key = "og9UTrj8I83ndelDQrzlpjXS8HwtiQVMV2S_v7D1";
    token.m_secret_key = "oGUsG0nvsCcltrlkci08qY48DaM-uC7MQjsWRPe0";


    QINIU_NAMESPACE::IQiniuRemoteFile* qiniuInterface = QINIU_NAMESPACE::QiniuFactory::CreateIQiniuRemoteFileObj();

    QINIU_NAMESPACE::QiniuCode code 
        = qiniuInterface->moveRemoteFile(token, "testqiniucppsdk", "a.txt", "testqiniucppsdk", "b.txt");

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
                             << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    code = qiniuInterface->moveRemoteFile(token, "testqiniucppsdk", "b.txt", "testqiniucppsdk", "a.txt");

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
                             << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    QINIU_NAMESPACE::QiniuFactory::DestoryIQiniuRemoteFileObj(qiniuInterface);
 
    QINIU_NAMESPACE::QiniuUtils::Terminate();

}



// ���Է���IQiniuRemoteFile::moveRemoteFile()
// �ƶ�/�����ļ�����ʧ��
TEST(IQiniuRemoteFileTest, TestCase1_moveRemoteFile)
{

    QINIU_NAMESPACE::QiniuUtils::Initialize();

    QINIU_NAMESPACE::QiniuToken token;

    token.m_access_key = "og9UTrj8I83ndelDQrzlpjXS8HwtiQVMV2S_v7D1";
    token.m_secret_key = "oGUsG0nvsCcltrlkci08qY48DaM-uC7MQjsWRPe0";


    QINIU_NAMESPACE::IQiniuRemoteFile* qiniuInterface = QINIU_NAMESPACE::QiniuFactory::CreateIQiniuRemoteFileObj();

    QINIU_NAMESPACE::QiniuCode code 
        = qiniuInterface->moveRemoteFile(token, "testqiniucppsdk", "aaaaaaa.txt", "testqiniucppsdk", "b.txt");

    GTEST_ASSERT_EQ((code << 16 >> 16), 612) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    code = qiniuInterface->moveRemoteFile(token, "testqiniucppsdk", "baaaaae.txt", "testqiniucppsdk", "a.txt");

    GTEST_ASSERT_EQ((code << 16 >> 16), 612) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    QINIU_NAMESPACE::QiniuFactory::DestoryIQiniuRemoteFileObj(qiniuInterface);


    QINIU_NAMESPACE::QiniuUtils::Terminate();

}

// ���Է���IQiniuRemoteFile::copyRemoteFile()   IQiniuRemoteFile::deleteRemoteFile()
// ����/ɾ���ļ�
TEST(IQiniuRemoteFileTest, TestCase0_copyRemoteFile_deleteRemoteFile)
{

    QINIU_NAMESPACE::QiniuUtils::Initialize();

    QINIU_NAMESPACE::QiniuToken token;

    token.m_access_key = "og9UTrj8I83ndelDQrzlpjXS8HwtiQVMV2S_v7D1";
    token.m_secret_key = "oGUsG0nvsCcltrlkci08qY48DaM-uC7MQjsWRPe0";


    QINIU_NAMESPACE::IQiniuRemoteFile* qiniuInterface = QINIU_NAMESPACE::QiniuFactory::CreateIQiniuRemoteFileObj();

    QINIU_NAMESPACE::QiniuCode code 
        = qiniuInterface->copyRemoteFile(token, "testqiniucppsdk", "a.txt", "testqiniucppsdk", "a-copy.txt");

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();


    code = qiniuInterface->deleteRemoteFile(token, "testqiniucppsdk", "a-copy.txt");

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();


    QINIU_NAMESPACE::QiniuFactory::DestoryIQiniuRemoteFileObj(qiniuInterface);


    QINIU_NAMESPACE::QiniuUtils::Terminate();

}


// ���Է��� IQiniuRemoteFile::deleteRemoteFile()
// ɾ���ļ�
TEST(IQiniuRemoteFileTest, TestCase0_deleteRemoteFile)
{

    QINIU_NAMESPACE::QiniuUtils::Initialize();

    QINIU_NAMESPACE::QiniuToken token;

    token.m_access_key = "og9UTrj8I83ndelDQrzlpjXS8HwtiQVMV2S_v7D1";
    token.m_secret_key = "oGUsG0nvsCcltrlkci08qY48DaM-uC7MQjsWRPe0";


    QINIU_NAMESPACE::IQiniuRemoteFile* qiniuInterface = QINIU_NAMESPACE::QiniuFactory::CreateIQiniuRemoteFileObj();

    
    QINIU_NAMESPACE::QiniuCode code = qiniuInterface->deleteRemoteFile(token, "testqiniucppsdk", "a.txt");

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    code = qiniuInterface->deleteRemoteFile(token, "testqiniucppsdk", "b.test");

    GTEST_ASSERT_EQ(code, 0) << "The code is : " << (code >> 16) << " | " << (code << 16 >> 16) 
        << "\nthe result is" << qiniuInterface->getLastErrorInfo();

    QINIU_NAMESPACE::QiniuFactory::DestoryIQiniuRemoteFileObj(qiniuInterface);
    QINIU_NAMESPACE::QiniuUtils::Terminate();
}



// 
// -----------------------------------------------------------------------------