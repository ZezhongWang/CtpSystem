#include "util/iniparser.h"

CIni::CIni( )
{
    memset( m_szKey,0,sizeof(m_szKey) );
    m_fp = NULL;
}

CIni::~CIni()
{
    m_Map.clear();
}

INI_RES CIni::OpenFile(const char* pathName, const char* type)
{
    string szLine,szMainKey,szLastMainKey,szSubKey;
    char strLine[ CONFIGLEN ] = { 0 };
    KEYMAP mLastMap;
    int  nIndexPos = -1;
    int  nLeftPos = -1;
    int  nRightPos = -1;
    m_fp = fopen(pathName, type);
    if (m_fp == NULL)
    {
        printf( "open inifile %s error!\n",pathName );
        return INI_OPENFILE_ERROR;
    }
    m_Map.clear();
    while( fgets( strLine, CONFIGLEN,m_fp) )
    {
        szLine.assign( strLine );
        nLeftPos = szLine.find("\n" );
        if( string::npos != nLeftPos )
        {
            szLine.erase( nLeftPos,1 );
        }
        nLeftPos = szLine.find("\r" );
        if( string::npos != nLeftPos )
        {
            szLine.erase( nLeftPos,1 );
        }
        nLeftPos = szLine.find("[");
        nRightPos = szLine.find("]");
        if(  nLeftPos != string::npos && nRightPos != string::npos )
        {
            szLine.erase( nLeftPos,1 );
            nRightPos--;
            szLine.erase( nRightPos,1 );
            m_Map[ szLastMainKey ] = mLastMap;
            mLastMap.clear();
            szLastMainKey =  szLine ;
        }
        else
        {
            if( nIndexPos = szLine.find("=" ),string::npos != nIndexPos)
            {
                string szSubKey,szSubValue;
                szSubKey = szLine.substr( 0,nIndexPos );
                szSubValue = szLine.substr( nIndexPos+1,szLine.length()-nIndexPos-1);
                mLastMap[szSubKey] = szSubValue ;
            }
            else
            {

            }
        }

    }
    m_Map[ szLastMainKey ] = mLastMap;
    return INI_SUCCESS;
}

INI_RES CIni::CloseFile()
{
    if (m_fp != NULL)
    {
        fclose(m_fp);
        m_fp = NULL;
    }

    return INI_SUCCESS;
}

INI_RES CIni::GetKey(const char* mAttr, const char* cAttr, char* pValue)
{

    KEYMAP mKey = m_Map[ mAttr ];

    string sTemp = mKey[ cAttr ];

    strcpy( pValue,sTemp.c_str() );

    return INI_SUCCESS;
}

int CIni::GetInt(const char* mAttr, const char* cAttr )
{
    int nRes = 0;
    memset( m_szKey,0,sizeof(m_szKey) );
    if( INI_SUCCESS == GetKey( mAttr,cAttr,m_szKey ) )
    {
        nRes = atoi( m_szKey );
    }
    return nRes;
}

char *CIni::GetStr(const char* mAttr, const char* cAttr )
{
    memset( m_szKey,0,sizeof(m_szKey) );
    if( INI_SUCCESS != GetKey( mAttr,cAttr,m_szKey ) )
    {
        strcpy( m_szKey,"NULL" );
    }
    return m_szKey;
}

Config* loadConfig(const char* filePath){
    CIni ini;
    INI_RES rtn = ini.OpenFile(filePath, "r");
    if (rtn == INI_SUCCESS ){
        Config *account = new Config();
        account->tdAddress = ini.GetStr("Account", "TD_ADDRESS");
        account->mdAddress = ini.GetStr("Account", "MD_ADDRESS");
        strcpy(account->brokerId, ini.GetStr("Account", "BROKER_ID"));
        strcpy(account->userId, ini.GetStr("Account", "USER_ID"));
        strcpy(account->passWord, ini.GetStr("Account", "PASSWORD"));
        return account;
    }
    else{
        cout<<"Load .ini "<<filePath<<"failed"<<endl;
    }
    return NULL;
}