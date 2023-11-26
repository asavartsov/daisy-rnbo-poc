#include "RNBO.h"
#include "daisy_seed.h"

using namespace daisy;
using namespace RNBO;

#define BLOCK_SIZE  4
#define NUM_INPUTS  2
#define NUM_OUTPUTS 2
#define SAMPLE_RATE 48000

static DaisySeed hw;
static RNBO::CoreObject *rnboObject;

RNBO::MidiEventList midiInputLists[] = { RNBO::MidiEventList(), RNBO::MidiEventList() };
RNBO::MidiEventList midiOutputLists[] = { RNBO::MidiEventList(), RNBO::MidiEventList() };

RNBO::MidiEventList *midiInputListForCallback = &midiInputLists[0];
RNBO::MidiEventList *midiOutputListForCallback = &midiOutputLists[0];
RNBO::MidiEventList *midiInputListForMain = &midiInputLists[1];
RNBO::MidiEventList *midiOutputListForMain = &midiOutputLists[1];

static void AudioCallback(AudioHandle::InputBuffer  in,
                          AudioHandle::OutputBuffer out,
                          size_t                    size)
{
    // Docs say that if sample rate or block size haven't been changed this
    // is basically no-op so it it safe to call it in audio callback.
    // But of course the code is still doing some checks and stuff so
    // it could be moved to the sample place where we set sample rate and
    // block size to Daisy. 
    rnboObject->prepareToProcess(SAMPLE_RATE, BLOCK_SIZE);

    // Previous RNBO versions had different in and out types so it will not
    // compile with some very old versions and require changing this call (remove const). 
    // There is a templated process function that may look like a good choice to use here,
    // but it is not. It is intended to deal with interleaved buffers and stuff like this
    // and it will use a converter that will allocate sample blocks in heap and copy buffers.
    rnboObject->process(
        (const SampleValue* const *) in, 
        NUM_INPUTS, 
        (SampleValue* const *) out, 
        NUM_OUTPUTS, 
        BLOCK_SIZE,
        midiInputListForCallback,
        midiOutputListForCallback
    );
}

// Simulates a changing parameter from 50 to 1000 and back to 50 wiht period of 5 seconds.
float getParameterValue() {
    float min = 50.0f;
    float max = 1000.0f;
    float duration = 5000.0f; // ms
    
    auto time = rnboObject->getCurrentTime();

    return min + max * (0.5f + sin(TWOPI * time / duration) / 2.0f);
}

int main(void) 
{
    hw.Init();
    hw.SetAudioBlockSize(BLOCK_SIZE);

    UniquePtr<PatcherInterface> patcher { nullptr };
    PatcherFactoryFunctionPtr factory = GetPatcherFactoryFunction(Platform::get());
    
    rnboObject = new RNBO::CoreObject(std::move(patcher = factory()));

    hw.StartAudio(AudioCallback);

    auto midiTime = rnboObject->getCurrentTime();
    int midiCounter = 0;

    auto paramId = rnboObject->getParameterIndexForID("freq");

    while (true) {
        auto timePassed = rnboObject->getCurrentTime() - midiTime;

        // As an example, let's do event processing at sample block rate
        if (timePassed > 0) {
            midiTime += timePassed;

            // Clock advanced, it means that all events processed by RNBO engine:
            // all input MIDI messages in queue were read and ouput messages were added.
            // If we are supplying MIDI event lists to the process method like it is done above,
            // we need to clear input event list, add some new input events and process
            // new output events, discarding them afterwards. But what if audio callback will
            // interrupt this while we are accessing the lists? I think it could be done in two ways.

            // First is an example of double-buffered MIDI events

            // Let's swap event lists and do main loop processing
            std::swap(midiInputListForCallback, midiInputListForMain);
            std::swap(midiOutputListForCallback, midiOutputListForMain);

            // Process input events
            midiInputListForMain->clear();
            midiInputListForMain->addEvent(RNBO::MidiEvent(midiTime, 0, 0x90, 0x3C, 0x64));

            // Process output events
            for (auto event: *midiOutputListForMain) {
                hw.SetLed(midiCounter++ > 1000);
                midiCounter = midiCounter % 2000;
            }
            midiOutputListForMain->clear();

            // Alternative to this could be scheduling input MIDI events directly like this
            // It looks much simplier, no need to manage an event list and clear it.
            rnboObject->scheduleEvent(RNBO::MidiEvent(midiTime, 0, 0x90, 0x3C, 0x64));

            // For output MIDI, it could be a custom EventHandler class (could be assigned to core object
            // constructor or via creating new ParameterInterfaceSync instance). 
            // It could be useful for receiving other types of events but wiht CoreEngine
            // all event processing is syncronous, so all handler methods will be called
            // from audio callback, so we will still want to save to some double-buffered
            // list for processing in the main loop.

            // Also let's process parameters at the sample block rate
            rnboObject->setParameterValue(paramId, getParameterValue());
        }
    }
}