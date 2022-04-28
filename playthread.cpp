//
// Created by bjke on 2022/4/27.
//

#include "playthread.h"
#include "SDL2/SDL.h"
#include <QFile>
#include "QDebug"

#define FILENAME "/Users/bjke/workspaces/c++/qt-sound/in.pcm"
#define SAMPLE_RATE 44100
#define SAMPLE_SIZE 16
#define CHANNELS 2
#define BUFFER_SIZE 4096

PlayThread::PlayThread(QObject *parent) : QThread(parent) {
    connect(this, &PlayThread::finished,
            this, &PlayThread::deleteLater);
}

PlayThread::~PlayThread() {
    disconnect();
    requestInterruption();
    quit();
    wait();
    qDebug() << this << "析构了";
}

int bufferLen;
char *bufferData;

// userdata：SDL_AudioSpec.userdata
// stream：音频缓冲区（需要将音频数据填充到这个缓冲区）
// len：音频缓冲区的大小（SDL_AudioSpec.samples * 每个样本的大小）
// 等待音频设备回调（会回调多次）
void pull_audio_data(void *userdata, Uint8 *stream, int len) {
    qDebug() << "pull_audio_data" << len;
    // 清空stream
    SDL_memset(stream, 0, len);
    // 文件数据还没准备好
    if (bufferLen<=0) return;
    // 取len，bufferlen的最小值 (为了保证数据安全，防止指针越界)
    len = (len>bufferLen) ? bufferLen:len;
    // 填充数据
    SDL_MixAudio(stream,(Uint8 *)bufferData,len,SDL_MIX_MAXVOLUME);
    bufferData += len;
    bufferLen -= len;
}

/**
 * SDL播放音频有2种模式
 * Push（推）:【程序】主动推送数据给【音频设备】
 * Push（拉）:【音频设备】主动向【程序】拉取数据
 */
void PlayThread::run() {
    // 初始化Audio子系统
    if (SDL_Init(SDL_INIT_AUDIO)) {
        // 返回值不是0,就代表失败
        qDebug() << "SDL_Init Error" << SDL_GetError();
        return;
    }
    // 音频参数
    SDL_AudioSpec spec;
    // 采样率
    spec.freq = SAMPLE_RATE;
    // 采样格式（s16le）
    spec.format = AUDIO_S16LSB;
    // 声道数
    spec.channels = CHANNELS;
    // 音频缓冲区的样本数量（必须是2的幂）
    spec.samples = 1024;
    // 回调
    spec.callback = pull_audio_data;
    // 打开设备
    if (SDL_OpenAudio(&spec, nullptr)) {
        // 返回值不是0,就代表失败
        qDebug() << "SDL_OpenAudio Error" << SDL_GetError();
        SDL_Quit();
        return;
    };

    // 打开文件
    QFile file(FILENAME);
    if (!file.open(QFile::ReadOnly)) {
        qDebug() << "文件打开失败" << FILENAME;
        // 关闭音频设备
        SDL_CloseAudio();
        // 清除所有初始化的子系统
        SDL_Quit();
        return;
    }

    // 开始播放(0是取消暂停)
    SDL_PauseAudio(0);
    // 存放从文件种读取的数据
    char data[BUFFER_SIZE];
    while (!isInterruptionRequested()) {
       bufferLen = file.read(data, BUFFER_SIZE);
       // 文件数据已经读完毕
       if(bufferLen<=0) break;

       // 读取到了文件数据
       bufferData = data;
       //等待音频数据填充完毕
       // 只要音频数据还没有填充完毕，就Delay(sleep)
        while (bufferLen>0){
            SDL_Delay(1);
        }
    }
    // 关闭文件
    file.close();
    ///关闭设备
    SDL_CloseAudio();
    // 清除所有子系统
    SDL_Quit();
}
