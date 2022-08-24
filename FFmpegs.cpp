//
// Created by bjke on 2022/5/18.
//

#include <QFile>
#include "FFmpegs.h"
#include <QDebug>

void FFmpegs::pcm2wav(WAVHeader &header, const char *pcmFilename, const char *wavFilename) {
    header.blockAlign = header.byteRate * header.numChannels >> 3;
    header.byteRate = header.sampleRate * header.blockAlign;
    // 打开pcm文件
    QFile pcmFile(pcmFilename);

    // 打开文件
    if (!pcmFile.open(QIODevice::ReadOnly)) {
        qDebug() << "打开文件失败" << pcmFilename;
        return;
    };
    header.dataChunkDataSize = pcmFile.size();
    header.riffChunkDataSize = header.dataChunkDataSize + sizeof(WAVHeader) - 8;

    // 打开wav文件
    QFile wavFile(wavFilename);

    if (!wavFile.open(QIODevice::WriteOnly)) {
        qDebug() << "打开文件失败" << wavFilename;
        pcmFile.close();
        return;
    };

    // 写入头部
    wavFile.write((const char *) &header, sizeof(WAVHeader));
    // 写入pcm数据
    // 写入pcm数据
    char buf[1024];
    qint64 size;
    while ((size = pcmFile.read(buf, sizeof (buf))) > 0) {
        wavFile.write(buf, size);
    }

    // 关闭文件
    pcmFile.close();
    wavFile.close();

}

FFmpegs::FFmpegs() {

};
