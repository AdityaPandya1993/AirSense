#include "CSIReceiver.h"

#include "DSPPipeline.h"
#include "CSIDriver.h"

CSIReceiver&
CSIReceiver::shared()
{
    static CSIReceiver receiver;
    return receiver;
}

CSIReceiver::CSIReceiver()
{
    _enabled = false;
}

bool CSIReceiver::begin()
{
    if (!CSIDriver::shared().started())
    {
        Serial.println("CSI Driver NOT Ready");

        _enabled = false;

        return false;
    }

    _enabled = true;

    Serial.println("CSI Receiver Initialized");

    return true;
}

bool CSIReceiver::isEnabled() const
{
    return _enabled;
}

void CSIReceiver::onCSIFrame(
    const CSIFrame& frame
)
{
    DSPPipeline::shared().process(frame);
}