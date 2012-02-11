#ifndef _DATAFORM_H_
#define _DATAFORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FUix.h>
#include <FSystem.h>

class DataForm :
	public Osp::Ui::Controls::Form,
	public Osp::Uix::ISensorEventListener
{

public:
	DataForm(void);
	virtual ~DataForm(void);
	bool Initialize(void);

public:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnUserEventReceivedN(RequestId requestId, Osp::Base::Collection::IList * pArgs);

	/* Osp::Uix::ISensorEventListener */
	virtual void OnDataReceived(Osp::Uix::SensorType sensorType, Osp::Uix::SensorData &sensorData, result r);

private:

	/* Ui Controls */
	Osp::Ui::Controls::Label * pAccelerationXValueLabel;
	Osp::Ui::Controls::Label * pAccelerationYValueLabel;
	Osp::Ui::Controls::Label * pAccelerationZValueLabel;

	Osp::Ui::Controls::Label * pMagneticXValueLabel;
	Osp::Ui::Controls::Label * pMagneticYValueLabel;
	Osp::Ui::Controls::Label * pMagneticZValueLabel;

	Osp::Ui::Controls::Label * pPitchValueLabel;
	Osp::Ui::Controls::Label * pRollValueLabel;
	Osp::Ui::Controls::Label * pAzimuthValueLabel;

	Osp::Ui::Controls::Label * pProximityValueLabel;

	/* SensorManager */
	Osp::Uix::SensorManager sensorManager;

	/* Requests */
	static const int REQUEST_ID_UPDATE_GUI = 101;

};

#endif	//_DATAFORM_H_
