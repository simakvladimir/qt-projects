#include "wavfile.h"

WavFile::WavFile(QObject *parent) :
    QObject(parent)
{
#ifdef  DEBUG
    printf("\ninside WavFile()");
#endif     /* -----  not DEBUG  ----- */
}

/* deconstructor */
WavFile::~WavFile()
{

#ifdef  DEBUG
    printf("\n~WavFile()");
#else      /* -----  not DEBUG  ----- */

#endif     /* -----  not DEBUG  ----- */
}


long int WavFile::getNumSamples()
{
    return maxInSamples;
}


int WavFile::getNumChannels()
{
    return nChannel;
}


int WavFile::getBitsPerSample()
{
    return bitsPerSample;
}


double WavFile::getSampleRateHz()
{
    return fs_hz;
}


int WavFile::ifMoreDataAvailable()
{
    if(numInSamples >= maxInSamples)
    {
        return 0;
    }
    return 1;
}


double WavFile::readCurrentInput()
{
    if( (gWavDataIn == NULL) || (maxInSamples <=0) || (numInSamples < 0) )
    {
        printf("\nInput file not ready (or not loaded) !!!\n");
        exit(1);
    }

    if( numInSamples >= maxInSamples)
    {
        printf("What you reading. Nothing is left to read, you crazy book-worm!!");
        exit(1);
    }
    return gWavDataIn[numInSamples++];
}


int WavFile::openWavFile(char* fileName)
{

#ifdef  DEBUG
    printf("\nopenWavFile function");
#endif     /* -----  not DEBUG  ----- */
    int i;
    //printf("Inside function.");
    FILE *pFile;
    unsigned int stat;
    char outBuffer[80];

    WAV_HDR* pWavHeader;
    CHUNK_HDR* pChunkHeader;

    short int* pU;
    unsigned char* pC;
    int sFlag;
    long int rMore;

    char* wBuffer;
    int wBufferLength;

    /* set the defaults values. */
    gWavDataIn = NULL;
    numInSamples = 0;
    maxInSamples = 0;

    /* allocate wav header */
    pWavHeader = new WAV_HDR;
    pChunkHeader = new CHUNK_HDR;

    if( NULL == pWavHeader )
    {
        errorDesc = "can't new headers";
        return (error = -1);
    }

    if( NULL == pChunkHeader )
    {
        errorDesc = "can't new headers";
        return (error = -1);
    }

    /*
     * open the wav file
     */
    pFile = fopen( fileName, "rb");
    if(pFile == NULL)
    {
        errorDesc = "Can't open wav file.";
        return (error = -1);
    }


    /*-----------------------------------------------------------------------------
     *  Now, we have load the file. Start reading data.
     *-----------------------------------------------------------------------------*/

    /* read riff/wav header */
    stat = fread((void*) pWavHeader, sizeof(WAV_HDR), (size_t)1, pFile);
    if(stat != 1)
    {
        errorDesc = "Header missing. May be format is not OK!";
        return (error = -1);
    }

    /* check format of header */
    for(i = 0; i < 4; i++)
    {
        outBuffer[i] = pWavHeader->rID[i];
    }
    outBuffer[4] = 0;
    if(strcmp(outBuffer, "RIFF") != 0) // tested.
    {
        errorDesc = "Bad RIFF format. I am not cool enough to support everything";
        return (error = -1);
    }

    for(i = 0; i < 4; i++)
    {
        outBuffer[i] = pWavHeader->wID[i];
    }
    outBuffer[4] = 0;

#ifdef DEBUG1
    std::cout<<"\noutBuffer: "<<outBuffer<<"and fID:"<<pWavHeader->fId;
#else      /* -----  not >DEBUG  ----- */

#endif     /* -----  not >DEBUG  ----- */

    if(strcmp(outBuffer, "WAVE") != 0) // tested.
    {
        errorDesc = "Bad WAVE format";
        return (error = -1);
    }

    for(i = 0; i < 4; i++)
    {
        outBuffer[i] = pWavHeader->fId[i];
    }
    outBuffer[4] = 0;

#ifdef DEBUG1
    std::cout<<"outBuffer:"<<outBuffer;
    std::cout<<"compare:"<<strcmp(outBuffer, "fmt ");
#endif     /* -----  not >DEBUG  ----- */

    if(strcmp(outBuffer, "fmt ") != 0) // not with "fmt" since 4th pos is blank
    {
        errorDesc = "Bad fmt format";
        return (error = -1);
    }

    if(pWavHeader->wFormatTag != 1)
    {
        errorDesc = "Bad wav wFormatTag";
        return (error = -1);
    }

    if( (pWavHeader->numBitsPerSample != 16) && (pWavHeader->numBitsPerSample != 8))
    {
        printf("\nBad wav bits per sample");
    }

    /*
     * Skip over any remaining portion of wav header.
     */
    rMore = pWavHeader->pcmHeaderLength - (sizeof(WAV_HDR) - 20);
    if( 0 != fseek(pFile, rMore, SEEK_CUR))
    {
        printf("Can't seek.");
    }

    /*
     * read chunk untill a data chunk is found.
     */
    sFlag = 1;
    while(sFlag != 0)
    {
        // check attempts.
        if(sFlag > 10) { printf("\nToo manu chunks"); exit(-1);}

        // read chunk header
        stat = fread((void*)pChunkHeader, sizeof(CHUNK_HDR), (size_t)1, pFile);
        if( 1 != stat)
        {
            errorDesc = "I just can't read data. Sorry";
            return (error = -1);
        }

        // check chunk type.
        for(i =0; i < 4; i++)
        {
            outBuffer[i] = pChunkHeader->dId[i];
        }
        outBuffer[4] = 0;
        if(strcmp(outBuffer, "data") == 0) { break;}

        // skip over chunk.
        sFlag++;
        stat = fseek(pFile, pChunkHeader->dLen, SEEK_CUR);
        if(stat != 0)
        {
            errorDesc = "Can't seek.";
            return (error = -1);
        }

    }

    /* find length of remaining data. */
    wBufferLength = pChunkHeader->dLen;


#ifdef  DEBUG1
    std::cout<<"wBufferLength:"<<wBufferLength;
#endif     /* -----  not DEBUG  ----- */
    /* find number of samples. */
    maxInSamples = pChunkHeader->dLen;
    maxInSamples /= pWavHeader->numBitsPerSample/8;

    /* allocate new buffers */
    wBuffer = new char[wBufferLength];
    if( wBuffer == NULL)
    {
        printf("\nCan't allocate."); exit(-1);
    }

    gWavDataIn = new double[maxInSamples];
    if(gWavDataIn == NULL)
    {
        printf("Can't allocate\n"); exit(-1);
    }

    /* read signal data */
    stat = fread((void*)wBuffer, wBufferLength, (size_t)1, pFile);
    if( 1 != stat)
    {
        errorDesc = "Can't read buffer";
        return (error = -1);
    }

    /* convert data */
    if(pWavHeader->numBitsPerSample == 16)
    {
        pU = (short*) wBuffer;
        for( i = 0; i < maxInSamples; i++)
        {
            gWavDataIn[i] = (double) (pU[i]);
        }
    }
    else
    {
        pC = (unsigned char*) wBuffer;
        for( i = 0; i < maxInSamples; i++)
        {
            gWavDataIn[i] = (double) (pC[i]);
        }
    }

#ifdef  DEBUG11
    for( i = 0; i < maxInSamples; i++)
    {
        printf("%d:%f\t",i, gWavDataIn[i]);
    }
#endif     /* -----  not DEBUG  ----- */

    /*
     * save all this.
     */
   fs_hz = (double) (pWavHeader->nSamplesPerSec);
   bitsPerSample = pWavHeader->numBitsPerSample;
   nChannel = pWavHeader->numChannels;

  /* reset and delete */
   numInSamples = 0;

   if(wBuffer != NULL) delete wBuffer;
   if(pWavHeader != NULL) delete pWavHeader;
   if(pChunkHeader != NULL) delete pChunkHeader;
   fclose(pFile);

   errorDesc = "Файл успешно прочитан";
   return (error = EXIT_SUCCESS);
}

int WavFile::displayInformation(char* fName)
{
#if 1
   /*
    * print the data.
    */
   printf("\n-----------------------------------------------------");
   printf("\nLoaded wav file : %s", fName);
   printf("\nSample rate: %1.01f (Hz)", fs_hz);
   printf("\nNumber of samples = %ld", maxInSamples);
   printf("\nBits per sample = %d", bitsPerSample);
   printf("\nNumber of channels = %d", nChannel);
   printf("\n----------------------------------------------------\n");
#endif

  return EXIT_SUCCESS;
}

//int WavFile::writeDataToFile()
//{
//    FILE* pFile;
//    int n;
//    pFile = fopen("speechData.dat", "w");
//    char header[50];
//    n = sprintf(header, "; Sample Rate %1f\n", fs_hz);
//    fprintf(pFile, header);
//    n = sprintf(header, "; Channels %d\n", nChannel);
//    fprintf(pFile, header);

//    for( int i = 0; i < maxInSamples; i++)
//    {
//       char data[30];
//       int n;
//       n = sprintf(data,"\t%1.9f\t%1.9f\n", i/fs_hz, gWavDataIn[i]/pow(2,bitsPerSample - 1)); // normalize it.
//       //pData = gWavDataIn[i];
//       fprintf(pFile, data);
//       //std::cout<<data;
//    }
//    fclose(pFile);
//    return EXIT_SUCCESS;

//}
