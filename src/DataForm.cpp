#include "DataForm.h"

using namespace Osp::Base;
using namespace Osp::Base::Collection;
using namespace Osp::Ui;
using namespace Osp::Ui::Controls;
using namespace Osp::Uix;

DataForm::DataForm(void) {
}

DataForm::~DataForm(void) {
}

bool DataForm::Initialize() {
  Construct(L"IDF_DATAFORM");
  return true;
}

result DataForm::OnInitializing(void) {
  result r = E_SUCCESS;

  pAccelerationXValueLabel = static_cast<Label *> (GetControl(L"IDC_ACCEL_X_VAL_LABEL"));
  pAccelerationYValueLabel = static_cast<Label *> (GetControl(L"IDC_ACCEL_Y_VAL_LABEL"));
  pAccelerationZValueLabel = static_cast<Label *> (GetControl(L"IDC_ACCEL_Z_VAL_LABEL"));

  pMagneticXValueLabel = static_cast<Label *> (GetControl(L"IDC_MAG_X_VAL_LABEL"));
  pMagneticYValueLabel = static_cast<Label *> (GetControl(L"IDC_MAG_Y_VAL_LABEL"));
  pMagneticZValueLabel = static_cast<Label *> (GetControl(L"IDC_MAG_Z_VAL_LABEL"));

  pPitchValueLabel = static_cast<Label *> (GetControl(L"IDC_PITCH_VAL_LABEL"));
  pRollValueLabel = static_cast<Label *> (GetControl(L"IDC_ROLL_VAL_LABEL"));
  pAzimuthValueLabel = static_cast<Label *> (GetControl(L"IDC_AZIMUTH_VAL_LABEL"));

  pProximityValueLabel = static_cast<Label *> (GetControl(L"IDC_PROX_VAL_LABEL"));

  /* Initialize the SensorManager */
  sensorManager.Construct();

  long minimumSensorInterval;

  /* Check if this sensor is available */
  if (sensorManager.IsAvailable(SENSOR_TYPE_ACCELERATION)) {

    /* Obtain the minimum supported time interval between each read */
    sensorManager.GetMinInterval(SENSOR_TYPE_ACCELERATION, minimumSensorInterval);
    /* Add the sensor event listener (this form) to the sensor manager */
    sensorManager.AddSensorListener(*this, SENSOR_TYPE_ACCELERATION, minimumSensorInterval, true);
    /* Check for errors */
    if (IsFailed(r)) return E_FAILURE;

  }

  if (sensorManager.IsAvailable(SENSOR_TYPE_TILT)) {

    sensorManager.GetMinInterval(SENSOR_TYPE_TILT, minimumSensorInterval);
    sensorManager.AddSensorListener(*this, SENSOR_TYPE_TILT, minimumSensorInterval, true);
    if (IsFailed(r)) return E_FAILURE;

  }

  if (sensorManager.IsAvailable(SENSOR_TYPE_MAGNETIC)) {

    sensorManager.GetMinInterval(SENSOR_TYPE_MAGNETIC, minimumSensorInterval);
    sensorManager.AddSensorListener(*this, SENSOR_TYPE_MAGNETIC, minimumSensorInterval, true);
    if (IsFailed(r)) return E_FAILURE;

  }

  if (sensorManager.IsAvailable(SENSOR_TYPE_PROXIMITY)) {

    sensorManager.GetMinInterval(SENSOR_TYPE_PROXIMITY, minimumSensorInterval);
    sensorManager.AddSensorListener(*this, SENSOR_TYPE_PROXIMITY, minimumSensorInterval, true);
    if (IsFailed(r)) return E_FAILURE;

  }

  return r;
}

result DataForm::OnTerminating(void) {
  result r = E_SUCCESS;

  if (sensorManager.IsAvailable(SENSOR_TYPE_ACCELERATION))
    sensorManager.RemoveSensorListener(*this, SENSOR_TYPE_ACCELERATION);

  if (sensorManager.IsAvailable(SENSOR_TYPE_TILT))
    sensorManager.RemoveSensorListener(*this, SENSOR_TYPE_TILT);

  if (sensorManager.IsAvailable(SENSOR_TYPE_MAGNETIC))
    sensorManager.RemoveSensorListener(*this, SENSOR_TYPE_MAGNETIC);

  if (sensorManager.IsAvailable(SENSOR_TYPE_PROXIMITY))
    sensorManager.RemoveSensorListener(*this, SENSOR_TYPE_PROXIMITY);

  return r;
}

void DataForm::OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList * pArgs) {

  /* Retrieve the arguments */
  Integer * sensorTypeArg = static_cast<Integer *> (pArgs->GetAt(0));

  switch (sensorTypeArg->ToInt()) {
    case SENSOR_TYPE_ACCELERATION: {

      Float * xVal = static_cast<Float *> (pArgs->GetAt(1));
      Float * yVal = static_cast<Float *> (pArgs->GetAt(2));
      Float * zVal = static_cast<Float *> (pArgs->GetAt(3));

      String xString;
      xString.Append(xVal->ToFloat());
      xString.Append(" g");

      String yString;
      yString.Append(yVal->ToFloat());
      yString.Append(" g");

      String zString;
      zString.Append(zVal->ToFloat());
      zString.Append(" g");

      pAccelerationXValueLabel->SetText(xString);
      pAccelerationYValueLabel->SetText(yString);
      pAccelerationZValueLabel->SetText(zString);

    }
      break;

    case SENSOR_TYPE_MAGNETIC: {

      Float * xVal = static_cast<Float *> (pArgs->GetAt(1));
      Float * yVal = static_cast<Float *> (pArgs->GetAt(2));
      Float * zVal = static_cast<Float *> (pArgs->GetAt(3));

      String xString;
      xString.Append(xVal->ToFloat());
      xString.Append(L" µT");

      String yString;
      yString.Append(yVal->ToFloat());
      yString.Append(L" µT");

      String zString;
      zString.Append(zVal->ToFloat());
      zString.Append(L" µT");

      pMagneticXValueLabel->SetText(xString);
      pMagneticYValueLabel->SetText(yString);
      pMagneticZValueLabel->SetText(zString);
    }
      break;

    case SENSOR_TYPE_TILT: {

      Float * pitchVal = static_cast<Float *> (pArgs->GetAt(1));
      Float * rollVal = static_cast<Float *> (pArgs->GetAt(2));
      Float * azimuthVal = static_cast<Float *> (pArgs->GetAt(3));

      String pitchString;
      pitchString.Append(pitchVal->ToFloat());
      pitchString.Append(" °");

      String rollString;
      rollString.Append(rollVal->ToFloat());
      rollString.Append(" °");

      String azimuthString;
      azimuthString.Append(azimuthVal->ToFloat());
      azimuthString.Append(" °");

      pPitchValueLabel->SetText(pitchString);
      pRollValueLabel->SetText(rollString);
      pAzimuthValueLabel->SetText(azimuthString);
    }
      break;

    case SENSOR_TYPE_PROXIMITY: {

      Boolean * proximityVal = static_cast<Boolean *> (pArgs->GetAt(1));

      String proximityString;
      proximityString.Append(proximityVal->ToBool());

      pProximityValueLabel->SetText(proximityString);

    }
      break;
    case SENSOR_TYPE_GPS: {
      // Not used, but a warning is raised if this is missing
    }
      break;

  }

  /* Delete the arguments list */
  pArgs->RemoveAll(true);
  delete pArgs;

  RequestRedraw(true);

}

void DataForm::OnDataReceived(SensorType sensorType, SensorData &sensorData, result r) {

  ArrayList * args = new ArrayList();
  args->Add(*new Integer(sensorType));

  switch (sensorType) {
    case SENSOR_TYPE_ACCELERATION: {
      float x, y, z;

      sensorData.GetValue((SensorDataKey) ACCELERATION_DATA_KEY_X, x);
      sensorData.GetValue((SensorDataKey) ACCELERATION_DATA_KEY_Y, y);
      sensorData.GetValue((SensorDataKey) ACCELERATION_DATA_KEY_Z, z);

      Float * accelerationX = new Float(x);
      Float * accelerationY = new Float(y);
      Float * accelerationZ = new Float(z);

      args->Add(*accelerationX);
      args->Add(*accelerationY);
      args->Add(*accelerationZ);

    }
      break;

    case SENSOR_TYPE_MAGNETIC: {
      float x, y, z;

      sensorData.GetValue((SensorDataKey) MAGNETIC_DATA_KEY_X, x);
      sensorData.GetValue((SensorDataKey) MAGNETIC_DATA_KEY_Y, y);
      sensorData.GetValue((SensorDataKey) MAGNETIC_DATA_KEY_Z, z);

      Float * accelerationX = new Float(x);
      Float * accelerationY = new Float(y);
      Float * accelerationZ = new Float(z);

      args->Add(*accelerationX);
      args->Add(*accelerationY);
      args->Add(*accelerationZ);
    }
      break;

    case SENSOR_TYPE_TILT: {
      float pitch, roll, azimuth;

      sensorData.GetValue((SensorDataKey) TILT_DATA_KEY_PITCH, pitch);
      sensorData.GetValue((SensorDataKey) TILT_DATA_KEY_ROLL, roll);
      sensorData.GetValue((SensorDataKey) TILT_DATA_KEY_AZIMUTH, azimuth);

      Float * fPitch = new Float(pitch);
      Float * fRoll = new Float(roll);
      Float * fAzimuth = new Float(azimuth);

      args->Add(*fPitch);
      args->Add(*fRoll);
      args->Add(*fAzimuth);
    }
      break;

    case SENSOR_TYPE_PROXIMITY: {
      bool status;

      sensorData.GetValue((SensorDataKey) PROXIMITY_DATA_KEY_ONOFF, status);

      Boolean * bStatus = new Boolean(status);

      args->Add(*bStatus);

    }
      break;
    case SENSOR_TYPE_GPS: {
      // Not used, but a warning is raised if this is missing
    }
      break;

  }

  SendUserEvent(REQUEST_ID_UPDATE_GUI, args);

}

