#include "oSound.h"
#include <dsound.h>
#include <fstream>
using std::fstream;
using std::ios;

typedef char oInt8;
typedef unsigned int oUInt32;
typedef int oInt32;
typedef unsigned char oUInt8;

oSound::oSound():
m_lpkSound(NULL){ }

oSound::~oSound()
{
	oSound::Release();
}

bool oSound::LoadFromFile( const char* filename )
{
	fstream kWave;
	/*打开波形文件*/
	kWave.open(filename,ios::in|ios::binary);
	if (kWave.is_open())
	{
		oInt8 aiID[5];
		/*读取文件标识符"RIFF"*/
		kWave.read(aiID,sizeof(oInt8)*4);
		aiID[4] = '\0';
		/*如果标识符不是"RIFF"，就退出并返回错误代码*/
		if (0 != strcmp(aiID,"RIFF"))
		{
			return false;
		}
		oUInt32 iSize;
		/*读取波形数据大小*/
		kWave.read((oInt8*)&iSize,sizeof(oUInt32));
		/*读取类型标识符"WAVE"*/
		kWave.read(aiID,sizeof(oInt8)*4);
		aiID[4] = '\0';
		/*如果类型标识符不是"WAVE",就退出并返回错误代码*/
		if (0 != strcmp(aiID,"WAVE"))
		{
			return false;
		}
		/*忽略"FMT"字符串*/
		kWave.seekg(4,ios::cur);
		/*读取格式快长度*/
		oUInt32 iFormatLength;
		kWave.read((oInt8*)&iFormatLength,sizeof(oUInt32));
		/*读取WAVEFORMATEX结构体*/
		WAVEFORMATEX kWaveFormat;
		kWave.read((oInt8*)&kWaveFormat,sizeof(WAVEFORMATEX));
		/*前面由于WAVEFORMATEX的cbSize多读了两个字节，现在忽略两个字节*/
		kWave.seekg(2,ios::cur);
		kWaveFormat.cbSize = 0;
		/*读取波形数据大小*/
		oUInt32 iDataSize;
		kWave.read((oInt8*)&iDataSize,sizeof(oUInt32));
		/*读取声音数据*/
		oUInt8 *pkSoundBuffer = new oUInt8[iDataSize];
		kWave.read((oInt8*)pkSoundBuffer,sizeof(oUInt8)*iDataSize);
		/*填充DirectSound缓冲区描述信息*/
		DSBUFFERDESC kBufferDesc;
		ZeroMemory(&kBufferDesc,sizeof(DSBUFFERDESC));
		kBufferDesc.dwSize = sizeof(DSBUFFERDESC);
		kBufferDesc.dwBufferBytes = iDataSize;
		kBufferDesc.lpwfxFormat = &kWaveFormat;
		kBufferDesc.dwFlags = DSBCAPS_CTRLVOLUME;
		/*创建声音缓冲区*/
		if (FAILED(((LPDIRECTSOUND8)(oSoundPlayer::Instance().GetDevice()))->CreateSoundBuffer(&kBufferDesc,
			(LPDIRECTSOUNDBUFFER*)(&m_lpkSound),NULL)))
		{
			return false;
		}
		/*锁定缓冲区*/
		LPVOID lpvAudio;
		DWORD dwBytes;
		if (FAILED(((LPDIRECTSOUNDBUFFER)m_lpkSound)->Lock(0,0,&lpvAudio,&dwBytes,NULL,NULL,DSBLOCK_ENTIREBUFFER)))
		{
			return false;
		}
		/*将波形数据拷贝到DirextSound缓冲区*/
		memcpy(lpvAudio,pkSoundBuffer,dwBytes);
		((LPDIRECTSOUNDBUFFER)m_lpkSound)->Unlock(lpvAudio,dwBytes,NULL,0);
		/*删除储存波形数据的内存，然后关闭文件*/
		delete [] pkSoundBuffer;
		kWave.close();
	}
	return m_lpkSound ? true : false;
}

void oSound::SetVolume( float volume )
{
	((LPDIRECTSOUNDBUFFER)m_lpkSound)->SetVolume(volume == 0.0f ? -10000 : (long)(-30*(100*volume)));
}

void oSound::Play( bool bLoop )
{
	((LPDIRECTSOUNDBUFFER)m_lpkSound)->Stop();
	/*将起始位置设为播放位置*/
	((LPDIRECTSOUNDBUFFER)m_lpkSound)->SetCurrentPosition(0);
	/*播放声音*/
	((LPDIRECTSOUNDBUFFER)m_lpkSound)->Play(0,NULL,(bLoop ? DSBPLAY_LOOPING : 0));
}

void oSound::Stop()
{
	((LPDIRECTSOUNDBUFFER)m_lpkSound)->Stop();
}

void oSound::Release()
{
	if (NULL != m_lpkSound)
	{
		((LPDIRECTSOUNDBUFFER)m_lpkSound)->Release();
		m_lpkSound = NULL;
	}
}
