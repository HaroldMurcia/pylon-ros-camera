// Copyright 2015 <Magazino GmbH>

#ifndef PYLON_CAMERA_INTERNAL_DART_H_
#define PYLON_CAMERA_INTERNAL_DART_H_

#include <string>
#include <vector>

#include <pylon_camera/internal/impl/pylon_camera_usb.hpp>

namespace pylon_camera
{

class PylonDARTCamera : public PylonUSBCamera
{
public:
    explicit PylonDARTCamera(Pylon::IPylonDevice* device);
    virtual ~PylonDARTCamera();

    virtual std::string typeName() const;

    virtual bool applyStartupSettings(const PylonCameraParameter& params);

    virtual bool setUserOutput(int output_id, bool value);


protected:
    virtual bool setupSequencer(const std::vector<float>& exposure_times, std::vector<float>& exposure_times_set);

    virtual bool grab(Pylon::CGrabResultPtr& grab_result);
};

PylonDARTCamera::PylonDARTCamera(Pylon::IPylonDevice* device) :
    PylonUSBCamera(device)
{
}

PylonDARTCamera::~PylonDARTCamera()
{
}

bool PylonDARTCamera::applyStartupSettings(const PylonCameraParameter& params)
{
    return PylonUSBCamera::applyStartupSettings(params);
}

bool PylonDARTCamera::setupSequencer(const std::vector<float>& exposure_times, std::vector<float>& exposure_times_set)
{
    ROS_ERROR("SEQUENCER FOR DART CAMERAS NOT YET IMPLEMENTED!!!");
    return false;
}

bool PylonDARTCamera::grab(Pylon::CGrabResultPtr& grab_result)
{
    try
    {
        // /!\ The dart camera device does not support waiting for frame trigger ready
        cam_->ExecuteSoftwareTrigger();

        // BaslerDebugDay: hard coded timeout of 5s makes most sense for all applications
        cam_->RetrieveResult(5000,  // ms
                             grab_result,
                             Pylon::TimeoutHandling_ThrowException);
        return true;
    }
    catch (const GenICam::GenericException &e)
    {
        if (cam_->IsCameraDeviceRemoved())
        {
            is_cam_removed_ = true;
        }
        else
        {
            ROS_ERROR_STREAM("An image grabbing exception in pylon camera occurred: " << e.GetDescription());
        }
    }
    return false;
}

bool PylonDARTCamera::setUserOutput(int output_id, bool value)
{
    ROS_ERROR("Dart camera has no digital output.");
    return false;
}

std::string PylonDARTCamera::typeName() const
{
    return "DART";
}

}  // namespace pylon_camera

#endif  // PYLON_CAMERA_INTERNAL_DART_H_
