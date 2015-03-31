#include "portaudiowrapper.h"
#include <QDebug>
#define SAMPLE_SILENCE  (0.0f)
#define NUM_CHANNELS    (2)

/*
 *
 */
typedef float SAMPLE;
typedef struct
{
    int          frameIndex;  /* Index into sample array. */
    int          maxFrameIndex;
    SAMPLE      *recordedSamples;
}
paTestData;
/* This routine will be called by the PortAudio engine when audio is needed.
   It may called at interrupt level on some machines so don't do anything
   that could mess up the system like calling malloc() or free().
*/
static int patestCallback( const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo* timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData )
{
//    paTestData *data = (paTestData*)userData;
    const SAMPLE *rptr = (const SAMPLE*)inputBuffer;
//    SAMPLE *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];

    SafeBuffer *user_fifo = static_cast<SafeBuffer*>(userData);
    qDebug() << "INNNNNN"<<*rptr;
    long framesToCalc;
    long i;
    int finished;
//    unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;

//    (void) outputBuffer; /* Prevent unused variable warnings. */
//    (void) timeInfo;
//    (void) statusFlags;
//    (void) userData;

//    if( framesLeft < framesPerBuffer )
//    {
//        framesToCalc = framesLeft;
//        finished = paComplete;
//    }
//    else
//    {
//        framesToCalc = framesPerBuffer;
//        finished = paContinue;
//    }

    framesToCalc =  NUM_CHANNELS == 2 ? framesPerBuffer / 2: framesPerBuffer;

    user_fifo->lock();

    user_fifo->clear();


    if( inputBuffer == NULL )
    {
        for( i=0; i<framesToCalc; i++ )
        {
            user_fifo->push(SAMPLE_SILENCE);  /* left */
            if( NUM_CHANNELS == 2 ) user_fifo->push(SAMPLE_SILENCE);  /* right */
        }
    }
    else
    {
        for( i=0; i<framesToCalc; i++ )
        {
            user_fifo->push(*rptr++); //*wptr++ = *rptr++;  /* left */
            if( NUM_CHANNELS == 2 ) user_fifo->push(*rptr++);  /* right */
        }
    }
    user_fifo->unlock();
//    data->frameIndex += framesToCalc;
    qDebug() << "INNNNNN LAAAAAAAAAAAAASSSSSSSSTTTT"<<*rptr;

    return 0;
}


/*
 *
 *
 */



PortAudioWrapper::PortAudioWrapper(QObject *parent, SafeBuffer *buf) :
    QObject(parent), fifo( buf )
{
    qDebug() << "INIT audio" <<  Pa_Initialize();

    PaStream *stream_local;
    stream = stream_local;
}

PortAudioWrapper::~PortAudioWrapper()
{
     qDebug() << Pa_Terminate();
}

QHash <QString,int> PortAudioWrapper::get_devices_names( void ){

    QHash <QString,int> ret_val;

    const PaDeviceInfo *device_info;

    int device_count = Pa_GetDeviceCount();

    for ( int device_iterator = 0; device_iterator < device_count; device_iterator++ )
    {
       device_info = Pa_GetDeviceInfo( device_iterator);
       ret_val.insert( device_info->name, device_iterator );
    }
    return ret_val;
}


int PortAudioWrapper::get_device_count( void )
{
    static paTestData data;
    int ret_val;

    ret_val = Pa_GetDeviceCount();

    const PaDeviceInfo *device_info;

    for ( int j = 0; j < ret_val; j++ )
    {
        device_info = Pa_GetDeviceInfo( j );
        qDebug() << device_info->name;
        qDebug() << "IN"<<device_info->maxInputChannels;
        qDebug() << "OUT" <<device_info->maxOutputChannels;
        qDebug() << device_info->defaultSampleRate;
    }

    PaStream *stream;
       PaError err;

       PaStreamParameters  inputParameters,
                           outputParameters;

       outputParameters.device = 13; /* default output device */
       outputParameters.channelCount = 2;       /* stereo output */
       outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
       outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
       outputParameters.hostApiSpecificStreamInfo = NULL;

       inputParameters.device = 13; /* default input device */
       inputParameters.channelCount = 2;                    /* stereo input */
       inputParameters.sampleFormat = paFloat32;
       inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
       inputParameters.hostApiSpecificStreamInfo = NULL;

       /* Record some audio. -------------------------------------------- */
       Pa_OpenStream(
                 &stream,
                 &inputParameters,
                 NULL,                  /* &outputParameters, */
                 48000,
                 256,
                 paClipOff,      /* we won't output out of range samples so don't bother clipping them */
                 patestCallback,
                 &data );
       /* Open an audio I/O stream. */

//       Pa_OpenStream(&stream,NULL,)
//       err = Pa_OpenDefaultStream( &stream,
//                                   0,          /* no input channels */
//                                   2,          /* stereo output */
//                                   paFloat32,  /* 32 bit floating point output */
//                                   44100,
//                                   256,        /* frames per buffer, i.e. the number
//                                                      of sample frames that PortAudio will
//                                                      request from the callback. Many apps
//                                                      may want to use
//                                                      paFramesPerBufferUnspecified, which
//                                                      tells PortAudio to pick the best,
//                                                      possibly changing, buffer size.*/
//                                   patestCallback, /* this is your callback function */
//                                   &data ); /*This is a pointer that will be passed to
//                                                      your callback*/

       Pa_StartStream( stream );
    return ret_val;
}

void PortAudioWrapper::configure_stream( int input_device, int output_device ){

    PaStreamParameters  inputParameters,
                        outputParameters;

    const PaStreamParameters  *p_inputParameters;
    const PaStreamParameters  *p_outputParameters;

    static paTestData data;

    if (output_device < 0) {
        p_outputParameters = NULL;
    } else {
        outputParameters.device = output_device; /* default output device */
        outputParameters.channelCount = 2;       /* stereo output */
        outputParameters.sampleFormat = paFloat32; /* 32 bit floating point output */
        outputParameters.suggestedLatency = Pa_GetDeviceInfo( outputParameters.device )->defaultLowOutputLatency;
        outputParameters.hostApiSpecificStreamInfo = NULL;
        p_outputParameters = &outputParameters;
    }

    if (input_device < 0) {
        p_inputParameters = NULL;
    } else {
        inputParameters.device = input_device; /* default input device */
        inputParameters.channelCount = 2;                    /* stereo input */
        inputParameters.sampleFormat = paFloat32;
        inputParameters.suggestedLatency = Pa_GetDeviceInfo( inputParameters.device )->defaultLowInputLatency;
        inputParameters.hostApiSpecificStreamInfo = NULL;
        p_inputParameters = &inputParameters;
    }

    qDebug() << "Open stream !!!" << Pa_OpenStream(
              &stream,
              p_inputParameters,
              p_outputParameters,                  /* &outputParameters, */
              48000,
              256,
              paClipOff,      /* we won't output out of range samples so don't bother clipping them */
              patestCallback,
              (void*)fifo );

}


void PortAudioWrapper::capture_audio_stream_start( void ){

    qDebug() << "Start stream !!!" <<Pa_StartStream( stream );

}

void PortAudioWrapper::capture_audio_stream_stop( void ){

    if ( stream ) qDebug() << "Stop stream !!!" << Pa_StopStream( stream );

}

int PortAudioWrapper::handler_routine( const void *inputBuffer, void *outputBuffer,
                                       unsigned long framesPerBuffer,
                                       const PaStreamCallbackTimeInfo* timeInfo,
                                       PaStreamCallbackFlags statusFlags,
                                       void *userData )
{
    paTestData *data = (paTestData*)userData;
    const SAMPLE *rptr = (const SAMPLE*)inputBuffer;
    SAMPLE *wptr = &data->recordedSamples[data->frameIndex * NUM_CHANNELS];

    qDebug() << "INNNNNN"<<*rptr;
//    qDebug() << "OUTTTTT"<<*(const SAMPLE*)outputBuffer;
    long framesToCalc;
    long i;
    int finished;
    unsigned long framesLeft = data->maxFrameIndex - data->frameIndex;

    (void) outputBuffer; /* Prevent unused variable warnings. */
    (void) timeInfo;
    (void) statusFlags;
    (void) userData;

    if( framesLeft < framesPerBuffer )
    {
        framesToCalc = framesLeft;
        finished = paComplete;
    }
    else
    {
        framesToCalc = framesPerBuffer;
        finished = paContinue;
    }

    if( inputBuffer == NULL )
    {
        for( i=0; i<framesToCalc; i++ )
        {
            *wptr++ = SAMPLE_SILENCE;  /* left */
            if( NUM_CHANNELS == 2 ) *wptr++ = SAMPLE_SILENCE;  /* right */
        }
    }
    else
    {
        for( i=0; i<framesToCalc; i++ )
        {
            *wptr++ = *rptr++;  /* left */
            if( NUM_CHANNELS == 2 ) *wptr++ = *rptr++;  /* right */
        }
    }
    data->frameIndex += framesToCalc;

    return 0;
}
