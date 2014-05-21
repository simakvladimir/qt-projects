#ifndef WAVFILE_H
#define WAVFILE_H

#include <QObject>

typedef struct{
    char rID[4];      // 'RIFF'
    long int rLen;

    char wID[4];      // 'WAVE'

    char fId[4];      // 'fmt'
    long int pcmHeaderLength;
    short int wFormatTag;
    short int numChannels;
    long int nSamplesPerSec;
    long int nAvgBytesPerSec;
    short int numBlockAlingn;
    short int numBitsPerSample;
} WAV_HDR;

/* header of wave file */
typedef struct
{
    char dId[4];  // 'data' or 'fact'
    long int dLen;
} CHUNK_HDR;

class WavFile : public QObject
{
    Q_OBJECT
public:
    explicit WavFile(QObject *parent = 0);
    ~WavFile();

   long int getNumSamples();

   int getNumChannels();

   int getBitsPerSample();

   double getSampleRateHz();

   int displayInformation(char* fileName);

   double readCurrentInput();

   int ifMoreDataAvailable();

   void setFileName(QString name) { fileName = name; }

   int getError() { return error; }
   QString getErrorDesc() { return errorDesc; }

protected:
   double fs_hz;
   int bitsPerSample;
   int nChannel;

   double* gWavDataIn;
   int numInSamples;
   long int maxInSamples;

   QString errorDesc;
   int     error;
   QString fileName;
           /* put friends here if he has any else, leave him all alone you crazy objects */


public:
    int openWavFile(char* fileName);

//   int writeDataToFile();

   int closeWavFile(FILE* pFile);
signals:
   void finished();

public slots:
   void slotOpenWavFile() { openWavFile(fileName.toLatin1().data()); finished(); }

};

#endif // WAVFILE_H
