#include "RNBO.h"
#include "RNBO_TimeConverter.h"
#include "daisy_seed.h"

using namespace daisy;
using namespace RNBO;

#define BLOCK_SIZE  4
#define NUM_INPUTS  2
#define NUM_OUTPUTS 2
#define SAMPLE_RATE 48000

static DaisySeed hw;
static RNBO::CoreObject *rnboObject;

RNBO::MidiEventList midiInput;
RNBO::MidiEventList midiOutput;

static void AudioCallback(AudioHandle::InputBuffer  in,
                          AudioHandle::OutputBuffer out,
                          size_t                    size)
{
    rnboObject->prepareToProcess(SAMPLE_RATE, BLOCK_SIZE);
    rnboObject->process(
        (float**) in, NUM_INPUTS, (float**) out, NUM_OUTPUTS, BLOCK_SIZE, &midiInput, &midiOutput
    );
}

int main(void) 
{
    hw.Init();
    hw.SetAudioBlockSize(BLOCK_SIZE);

    UniquePtr<PatcherInterface> patcher { nullptr };
    PatcherFactoryFunctionPtr factory = GetPatcherFactoryFunction(Platform::get());
    
    rnboObject = new RNBO::CoreObject(std::move(patcher = factory()));

    hw.StartAudio(AudioCallback);

    float frequency = 50.0f;
    float inc = 0.005f;
    int counter = 0;

    while (true) {
        auto now = rnboObject->getCurrentTime();
        auto event = RNBO::MidiEvent(now, 0, 0x90, 0x3C, 0x64);
        
        midiInput.clearEventsBeforeTime(now);
        midiInput.addEvent(event);

        for (auto ptr = midiOutput.begin(); ptr < midiOutput.end(); ptr++) {
            hw.SetLed(counter++ > (SAMPLE_RATE / 32));
            counter = counter % (SAMPLE_RATE / 16);
        }

        midiOutput.clear();

        frequency += inc;

        if (frequency < 50 || frequency > 1000) {
            inc *= -1.0f;
        }
    
        rnboObject->setParameterValue(0, frequency);

        System::DelayTicks(10);
    }
}