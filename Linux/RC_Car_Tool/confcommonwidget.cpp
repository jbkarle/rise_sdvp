#include "confcommonwidget.h"
#include "ui_confcommonwidget.h"

#include <cstring>

ConfCommonWidget::ConfCommonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfCommonWidget)
{
    ui->setupUi(this);
}

ConfCommonWidget::~ConfCommonWidget()
{
    delete ui;
}

void ConfCommonWidget::getConfGui(MAIN_CONFIG &conf)
{
    conf.mag_use = ui->confMagUseBox->isChecked();
    conf.mag_comp = ui->confMagCompBox->isChecked();
    conf.yaw_mag_gain = ui->confYawMagGainBox->value();

    conf.mag_cal_cx = ui->confMagCxBox->value();
    conf.mag_cal_cy = ui->confMagCyBox->value();
    conf.mag_cal_cz = ui->confMagCzBox->value();
    conf.mag_cal_xx = ui->confMagXxBox->value();
    conf.mag_cal_xy = ui->confMagXyBox->value();
    conf.mag_cal_xz = ui->confMagXzBox->value();
    conf.mag_cal_yx = ui->confMagYxBox->value();
    conf.mag_cal_yy = ui->confMagYyBox->value();
    conf.mag_cal_yz = ui->confMagYzBox->value();
    conf.mag_cal_zx = ui->confMagZxBox->value();
    conf.mag_cal_zy = ui->confMagZyBox->value();
    conf.mag_cal_zz = ui->confMagZzBox->value();

    conf.gps_ant_x = ui->confGpsAntXBox->value();
    conf.gps_ant_y = ui->confGpsAntYBox->value();
    conf.gps_comp = ui->confGpsCorrBox->isChecked();
    conf.gps_req_rtk = ui->confGpsReqRtkBox->isChecked();
    conf.gps_corr_gain_stat = ui->confGpsCorrStatBox->value();
    conf.gps_corr_gain_dyn = ui->confGpsCorrDynBox->value();
    conf.gps_corr_gain_yaw = ui->confGpsCorrYawBox->value();
    conf.gps_send_nmea = ui->confGpsSendNmeaBox->isChecked();
    conf.gps_use_ubx_info = ui->confGpsUbxUseInfoBox->isChecked();
    conf.gps_ubx_max_acc = ui->confGpsUbxMaxAccBox->value();

    conf.ap_repeat_routes = ui->confApRepeatBox->isChecked();
    conf.ap_base_rad = ui->confApBaseRadBox->value();
    conf.ap_mode_time = ui->confApModeTimeBox->isChecked();
    conf.ap_max_speed = ui->confApMaxSpeedBox->value() / 3.6;
    conf.ap_time_add_repeat_ms = ui->confApAddRepeatTimeEdit->time().msecsSinceStartOfDay();

    conf.log_en = ui->confLogEnBox->isChecked();
    strcpy(conf.log_name, ui->confLogNameEdit->text().toLocal8Bit().data());
}

void ConfCommonWidget::setConfGui(const MAIN_CONFIG &conf)
{
    ui->confMagUseBox->setChecked(conf.mag_use);
    ui->confMagCompBox->setChecked(conf.mag_comp);
    ui->confYawMagGainBox->setValue(conf.yaw_mag_gain);

    ui->confMagCxBox->setValue(conf.mag_cal_cx);
    ui->confMagCyBox->setValue(conf.mag_cal_cy);
    ui->confMagCzBox->setValue(conf.mag_cal_cz);
    ui->confMagXxBox->setValue(conf.mag_cal_xx);
    ui->confMagXyBox->setValue(conf.mag_cal_xy);
    ui->confMagXzBox->setValue(conf.mag_cal_xz);
    ui->confMagYxBox->setValue(conf.mag_cal_yx);
    ui->confMagYyBox->setValue(conf.mag_cal_yy);
    ui->confMagYzBox->setValue(conf.mag_cal_yz);
    ui->confMagZxBox->setValue(conf.mag_cal_zx);
    ui->confMagZyBox->setValue(conf.mag_cal_zy);
    ui->confMagZzBox->setValue(conf.mag_cal_zz);

    ui->confGpsAntXBox->setValue(conf.gps_ant_x);
    ui->confGpsAntYBox->setValue(conf.gps_ant_y);
    ui->confGpsCorrBox->setChecked(conf.gps_comp);
    ui->confGpsReqRtkBox->setChecked(conf.gps_req_rtk);
    ui->confGpsCorrStatBox->setValue(conf.gps_corr_gain_stat);
    ui->confGpsCorrDynBox->setValue(conf.gps_corr_gain_dyn);
    ui->confGpsCorrYawBox->setValue(conf.gps_corr_gain_yaw);
    ui->confGpsSendNmeaBox->setChecked(conf.gps_send_nmea);
    ui->confGpsUbxUseInfoBox->setChecked(conf.gps_use_ubx_info);
    ui->confGpsUbxMaxAccBox->setValue(conf.gps_ubx_max_acc);

    ui->confApRepeatBox->setChecked(conf.ap_repeat_routes);
    ui->confApBaseRadBox->setValue(conf.ap_base_rad);
    ui->confApModeTimeBox->setChecked(conf.ap_mode_time);
    ui->confApMaxSpeedBox->setValue(conf.ap_max_speed * 3.6);
    ui->confApAddRepeatTimeEdit->setTime(QTime::fromMSecsSinceStartOfDay(conf.ap_time_add_repeat_ms));

    ui->confLogEnBox->setChecked(conf.log_en);
    ui->confLogNameEdit->setText(QString::fromLocal8Bit(conf.log_name));
}

void ConfCommonWidget::setMagComp(QVector<double> comp)
{
    if (comp.size() == 9) {
        ui->confMagXxBox->setValue(comp.at(0));
        ui->confMagXyBox->setValue(comp.at(1));
        ui->confMagXzBox->setValue(comp.at(2));

        ui->confMagYxBox->setValue(comp.at(3));
        ui->confMagYyBox->setValue(comp.at(4));
        ui->confMagYzBox->setValue(comp.at(5));

        ui->confMagZxBox->setValue(comp.at(6));
        ui->confMagZyBox->setValue(comp.at(7));
        ui->confMagZzBox->setValue(comp.at(8));
    }
}

void ConfCommonWidget::setMagCompCenter(QVector<double> center)
{
    if (center.size() == 3) {
        ui->confMagCxBox->setValue(center.at(0));
        ui->confMagCyBox->setValue(center.at(1));
        ui->confMagCzBox->setValue(center.at(2));
    }
}

void ConfCommonWidget::on_magCalLoadButton_clicked()
{
    emit loadMagCal();
}
