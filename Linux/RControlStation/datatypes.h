/*
    Copyright 2016-2017 Benjamin Vedder	benjamin@vedder.se

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DATATYPES_H_
#define DATATYPES_H_

#include <stdint.h>
#include <stdbool.h>

// Sizes
#define LOG_NAME_MAX_LEN			20

// Packet IDs
#define ID_ALL						255
#define ID_MOTE						254
#define ID_RTCM						211 // Same as RTCM3PREAMB

// Orientation data
typedef struct {
    float q0;
    float q1;
    float q2;
    float q3;
    float integralFBx;
    float integralFBy;
    float integralFBz;
    float accMagP;
    int initialUpdateDone;
} ATTITUDE_INFO;

typedef enum {
    FAULT_CODE_NONE = 0,
    FAULT_CODE_OVER_VOLTAGE,
    FAULT_CODE_UNDER_VOLTAGE,
    FAULT_CODE_DRV8302,
    FAULT_CODE_ABS_OVER_CURRENT,
    FAULT_CODE_OVER_TEMP_FET,
    FAULT_CODE_OVER_TEMP_MOTOR
} mc_fault_code;

typedef struct {
    uint8_t fw_major;
    uint8_t fw_minor;
    double roll;
    double pitch;
    double yaw;
    double accel[3];
    double gyro[3];
    double mag[3];
    double px;
    double py;
    double speed;
    double vin;
    double temp_fet;
    mc_fault_code mc_fault;
    double px_gps;
    double py_gps;
    double ap_goal_px;
    double ap_goal_py;
    double ap_rad;
    int32_t ms_today;
} CAR_STATE;

typedef struct {
    uint8_t fw_major;
    uint8_t fw_minor;
    double roll;
    double pitch;
    double yaw;
    double accel[3];
    double gyro[3];
    double mag[3];
    double px;
    double py;
    double pz;
    double speed;
    double vin;
    double px_gps;
    double py_gps;
    double ap_goal_px;
    double ap_goal_py;
    int32_t ms_today;
} MULTIROTOR_STATE;

typedef enum {
    MOTE_PACKET_FILL_RX_BUFFER = 0,
    MOTE_PACKET_FILL_RX_BUFFER_LONG,
    MOTE_PACKET_PROCESS_RX_BUFFER,
    MOTE_PACKET_PROCESS_SHORT_BUFFER,
} MOTE_PACKET;

typedef struct {
    bool yaw_use_odometry; // Use odometry data for yaw angle correction.
    float yaw_imu_gain; // Gain for yaw angle from IMU (vs odometry)
    bool disable_motor; // Disable motor drive commands to make sure that the motor does not move.

    float gear_ratio;
    float wheel_diam;
    float motor_poles;
    float steering_max_angle_rad; // = arctan(axist_distance / turn_radius_at_maximum_steering_angle)
    float steering_center;
    float steering_range;
    float steering_ramp_time; // Ramp time constant for the steering servo in seconds
    float axis_distance;
} MAIN_CONFIG_CAR;

typedef struct {
    // Dead reckoning
    float vel_decay_e;
    float vel_decay_l;
    float vel_max;
    float map_min_x;
    float map_max_x;
    float map_min_y;
    float map_max_y;

    // State correction for dead reckoning
    float vel_gain_p;
    float vel_gain_i;
    float vel_gain_d;

    float tilt_gain_p;
    float tilt_gain_i;
    float tilt_gain_d;

    float max_corr_error;
    float max_tilt_error;

    // Attitude controller
    float ctrl_gain_roll_p;
    float ctrl_gain_roll_i;
    float ctrl_gain_roll_dp;
    float ctrl_gain_roll_de;

    float ctrl_gain_pitch_p;
    float ctrl_gain_pitch_i;
    float ctrl_gain_pitch_dp;
    float ctrl_gain_pitch_de;

    float ctrl_gain_yaw_p;
    float ctrl_gain_yaw_i;
    float ctrl_gain_yaw_dp;
    float ctrl_gain_yaw_de;

    // Position controller
    float ctrl_gain_pos_p;
    float ctrl_gain_pos_i;
    float ctrl_gain_pos_d;

    // Altitude controller
    float ctrl_gain_alt_p;
    float ctrl_gain_alt_i;
    float ctrl_gain_alt_d;

    // Joystick gain
    float js_gain_tilt;
    float js_gain_yaw;
    bool js_mode_rate;

    // Motor mapping and configuration
    int8_t motor_fl_f; // x: Front Left  +: Front
    int8_t motor_bl_l; // x: Back Left   +: Left
    int8_t motor_fr_r; // x: Front Right +: Right
    int8_t motor_br_b; // x: Back Right  +: Back
    bool motors_x; // Use x motor configuration (use + if false)
    bool motors_cw; // Front left (or front in + mode) runs in the clockwise direction (ccw if false)
    uint16_t motor_pwm_min_us; // Minimum servo pulse length for motor in microseconds
    uint16_t motor_pwm_max_us; // Maximum servo pulse length for motor in microseconds
} MAIN_CONFIG_MULTIROTOR;

// Car configuration
typedef struct {
    // Common vehicle settings
    bool mag_use; // Use the magnetometer
    bool mag_comp; // Should be 0 when capturing samples for the calibration
    float yaw_mag_gain; // Gain for yaw angle from magnetomer (vs gyro)

    // Magnetometer calibration
    float mag_cal_cx;
    float mag_cal_cy;
    float mag_cal_cz;
    float mag_cal_xx;
    float mag_cal_xy;
    float mag_cal_xz;
    float mag_cal_yx;
    float mag_cal_yy;
    float mag_cal_yz;
    float mag_cal_zx;
    float mag_cal_zy;
    float mag_cal_zz;

    // GPS parameters
    float gps_ant_x; // Antenna offset from vehicle center in X
    float gps_ant_y; // Antenna offset from vehicle center in Y
    bool gps_comp; // Use GPS position correction
    bool gps_req_rtk; // Require RTK solution
    float gps_corr_gain_stat; // Static GPS correction gain
    float gps_corr_gain_dyn; // Dynamic GPS correction gain
    float gps_corr_gain_yaw; // Gain for yaw correction
    bool gps_send_nmea; // Send NMEA data for logging and debugging
    bool gps_use_ubx_info; // Use info about the ublox solution
    float gps_ubx_max_acc; // Maximum ublox accuracy to use solution (m, higher = worse)

    // Autopilot parameters
    bool ap_repeat_routes; // Repeat the same route when the end is reached
    float ap_base_rad; // Radius around car at 0 speed
    bool ap_mode_time; // Drive to route points based on timestamps instead of speed
    float ap_max_speed; // Maximum allowed speed for autopilot
    int32_t ap_time_add_repeat_ms; // Time to add to each point for each repetition of the route

    // Logging
    bool log_en;
    char log_name[LOG_NAME_MAX_LEN + 1];

    MAIN_CONFIG_CAR car;
    MAIN_CONFIG_MULTIROTOR mr;
} MAIN_CONFIG;

// Commands
typedef enum {
    // General commands
    CMD_PRINTF = 0,
    CMD_TERMINAL_CMD,

    // Common vehicle commands
    CMD_VESC_FWD = 50,
    CMD_SET_POS,
    CMD_SET_POS_ACK,
    CMD_SET_ENU_REF,
    CMD_GET_ENU_REF,
    CMD_AP_ADD_POINTS,
    CMD_AP_REMOVE_LAST_POINT,
    CMD_AP_CLEAR_POINTS,
    CMD_AP_SET_ACTIVE,
    CMD_AP_REPLACE_ROUTE,
    CMD_SEND_RTCM_USB,
    CMD_SEND_NMEA_RADIO,
    CMD_SET_YAW_OFFSET,
    CMD_SET_YAW_OFFSET_ACK,
    CMD_LOG_LINE_USB,
    CMD_PLOT_INIT,
    CMD_PLOT_DATA,
    CMD_SET_MS_TODAY,
    CMD_SET_SYSTEM_TIME,
    CMD_SET_SYSTEM_TIME_ACK,
    CMD_REBOOT_SYSTEM,
    CMD_REBOOT_SYSTEM_ACK,
    CMD_RADAR_SETUP_SET,
    CMD_RADAR_SETUP_GET,
    CMD_RADAR_SAMPLES,
    CMD_DW_SAMPLE,
    CMD_EMERGENCY_STOP,
    CMD_SET_MAIN_CONFIG,
    CMD_GET_MAIN_CONFIG,
    CMD_GET_MAIN_CONFIG_DEFAULT,

    // Car commands
    CMD_GET_STATE = 120,
    CMD_RC_CONTROL,
    CMD_SET_SERVO_DIRECT,

    // Multirotor commands
    CMD_MR_GET_STATE = 160,
    CMD_MR_RC_CONTROL,
    CMD_MR_OVERRIDE_POWER,

    // Mote commands
    CMD_MOTE_UBX_START_BASE = 200,
    CMD_MOTE_UBX_START_BASE_ACK,
    CMD_MOTE_UBX_BASE_STATUS
} CMD_PACKET;

// RC control modes
typedef enum {
    RC_MODE_CURRENT = 0,
    RC_MODE_DUTY,
    RC_MODE_PID,
    RC_MODE_CURRENT_BRAKE
} RC_MODE;

typedef struct {
    bool log_en;
    float f_center;
    float f_span;
    int points;
    float t_sweep;
    float cc_x;
    float cc_y;
    float cc_rad;
    int log_rate_ms;
    float map_plot_avg_factor;
    float map_plot_max_div;
    int plot_mode; // 0 = off, 1 = sample, 2 = fft
    int map_plot_start;
    int map_plot_end;
} radar_settings_t;

// DW Logging Info
typedef struct {
    bool valid;
    uint8_t dw_anchor;
    int32_t time_today_ms;
    float dw_dist;
    float px;
    float py;
    float px_gps;
    float py_gps;
    float pz_gps;
} DW_LOG_INFO;

typedef enum {
    JS_TYPE_HK = 0,
    JS_TYPE_PS4,
    JS_TYPE_PS3
} JS_TYPE;

// ============== RTCM Datatypes ================== //

typedef struct {
    double t_tow;       // Time of week (GPS)
    double t_tod;       // Time of day (GLONASS)
    double t_wn;        // Week number
    int staid;          // ref station id
    bool sync;          // True if more messages are coming
    int type;           // RTCM Type
} rtcm_obs_header_t;

typedef struct {
    double P[2];        // Pseudorange observation
    double L[2];        // Carrier phase observation
    uint8_t cn0[2];     // Carrier-to-Noise density [dB Hz]
    uint8_t lock[2];    // Lock. Set to 0 when the lock has changed, 127 otherwise. TODO: is this correct?
    uint8_t prn;        // Sattelite
    uint8_t freq;       // Frequency slot (GLONASS)
    uint8_t code[2];    // Code indicator
} rtcm_obs_t;

typedef struct {
    int staid;
    double lat;
    double lon;
    double height;
    double ant_height;
} rtcm_ref_sta_pos_t;

typedef struct {
    double tgd;           // Group delay differential between L1 and L2 [s]
    double c_rs;          // Amplitude of the sine harmonic correction term to the orbit radius [m]
    double c_rc;          // Amplitude of the cosine harmonic correction term to the orbit radius [m]
    double c_uc;          // Amplitude of the cosine harmonic correction term to the argument of latitude [rad]
    double c_us;          // Amplitude of the sine harmonic correction term to the argument of latitude [rad]
    double c_ic;          // Amplitude of the cosine harmonic correction term to the angle of inclination [rad]
    double c_is;          // Amplitude of the sine harmonic correction term to the angle of inclination [rad]
    double dn;            // Mean motion difference [rad/s]
    double m0;            // Mean anomaly at reference time [radians]
    double ecc;           // Eccentricity of satellite orbit
    double sqrta;         // Square root of the semi-major axis of orbit [m^(1/2)]
    double omega0;        // Longitude of ascending node of orbit plane at weekly epoch [rad]
    double omegadot;      // Rate of right ascension [rad/s]
    double w;             // Argument of perigee [rad]
    double inc;           // Inclination [rad]
    double inc_dot;       // Inclination first derivative [rad/s]
    double af0;           // Polynomial clock correction coefficient (clock bias) [s]
    double af1;           // Polynomial clock correction coefficient (clock drift) [s/s]
    double af2;           // Polynomial clock correction coefficient (rate of clock drift) [s/s^2]
    double toe_tow;       // Time of week [s]
    uint16_t toe_wn;      // Week number [week]
    double toc_tow;       // Clock reference time of week [s]
    int sva;              // SV accuracy (URA index)
    int svh;              // SV health (0:ok)
    int code;             // GPS/QZS: code on L2, GAL/CMP: data sources
    int flag;             // GPS/QZS: L2 P data flag, CMP: nav type
    double fit;           // fit interval (h)
    uint8_t prn;          // Sattelite
    uint8_t iode;         // Issue of ephemeris data
    uint16_t iodc;        // Issue of clock data
} rtcm_ephemeris_t;

typedef struct {
    int buffer_ptr;
    int len;
    uint8_t buffer[1100];
    rtcm_obs_header_t header;
    rtcm_obs_t obs[64];
    rtcm_ref_sta_pos_t pos;
    rtcm_ephemeris_t eph;
    void(*rx_rtcm_obs)(rtcm_obs_header_t *header, rtcm_obs_t *obs, int obs_num);
    void(*rx_rtcm_1005_1006)(rtcm_ref_sta_pos_t *pos);
    void(*rx_rtcm_1019)(rtcm_ephemeris_t *eph);
    void(*rx_rtcm)(uint8_t *data, int len, int type);
} rtcm3_state;

// ============== UBLOX Datatypes ================== //

typedef struct {
    uint16_t ref_station_id;
    uint32_t i_tow; // GPS time of week of the navigation epoch
    float pos_n; // Position north in meters
    float pos_e; // Position east in meters
    float pos_d; // Position down in meters
    float acc_n; // Accuracy north in meters
    float acc_e; // Accuracy east in meters
    float acc_d; // Accuracy down in meters
    bool fix_ok; // A valid fix
    bool diff_soln; // Differential corrections are applied
    bool rel_pos_valid; // Relative position components and accuracies valid
    int carr_soln; // fix_type 0: no fix, 1: float, 2: fix
} ubx_nav_relposned;

typedef struct {
    uint32_t i_tow; // GPS time of week of the navigation epoch
    uint32_t dur; // Passed survey-in observation time (s)
    double meanX; // Current survey-in mean position ECEF X coordinate
    double meanY; // Current survey-in mean position ECEF Y coordinate
    double meanZ; // Current survey-in mean position ECEF Z coordinate
    float meanAcc; // Current survey-in mean position accuracy
    uint32_t obs; // Number of position observations used during survey-in
    bool valid; // Survey-in position validity flag, 1 = valid, otherwise 0
    bool active; // Survey-in in progress flag, 1 = in-progress, otherwise 0
} ubx_nav_svin;

typedef struct {
    double pr_mes;
    double cp_mes;
    float do_mes;
    uint8_t gnss_id;
    uint8_t sv_id;
    uint8_t freq_id;
    uint16_t locktime;
    uint8_t cno;
    uint8_t pr_stdev;
    uint8_t cp_stdev;
    uint8_t do_stdev;
    bool pr_valid;
    bool cp_valid;
    bool half_cyc_valid;
    bool half_cyc_sub;
} ubx_rxm_rawx_obs;

typedef struct {
    double rcv_tow;
    uint16_t week;
    int8_t leaps;
    uint8_t num_meas;
    bool leap_sec;
    bool clk_reset;
    ubx_rxm_rawx_obs obs[64];
} ubx_rxm_rawx;

typedef struct {
    uint32_t baudrate;
    bool in_rtcm3;
    bool in_rtcm2;
    bool in_nmea;
    bool in_ubx;
    bool out_rtcm3;
    bool out_nmea;
    bool out_ubx;
} ubx_cfg_prt_uart;

typedef struct {
    bool lla; // Use lla instead of ecef
    int mode; // Mode. 0 = Disabled, 1 = Survey in, 2 = Fixed
    double ecefx_lat;
    double ecefy_lon;
    double ecefz_alt;
    float fixed_pos_acc; // Fixed position accuracy
    uint32_t svin_min_dur; // SVIN minimum duration (s)
    float svin_acc_limit; // SVIN accuracy limit
} ubx_cfg_tmode3;

typedef struct {
    bool apply_dyn; // Apply dynamic model settings
    bool apply_min_el; // Apply minimum elevation settings
    bool apply_pos_fix_mode; // Apply fix mode settings
    bool apply_pos_mask; // Apply position mask settings
    bool apply_time_mask; // Apply time mask settings
    bool apply_static_hold_mask; // Apply static hold settings
    bool apply_dgps; // Apply DGPS settings.
    bool apply_cno; // Apply CNO threshold settings (cnoThresh, cnoThreshNumSVs).
    bool apply_utc; // Apply UTC settings

    /*
     * Dynamic platform model:
     * 0: portable
     * 2: stationary
     * 3: pedestrian
     * 4: automotive
     * 5: sea
     * 6: airborne with <1g acceleration
     * 7: airborne with <2g acceleration
     * 8: airborne with <4g acceleration
     * 9: wrist worn watch
     */
    uint8_t dyn_model;

    /*
     * Position Fixing Mode:
     * 1: 2D only
     * 2: 3D only
     * 3: auto 2D/3D
     */
    uint8_t fix_mode;

    double fixed_alt; // Fixed altitude (mean sea level) for 2D fix mode. (m)
    double fixed_alt_var; // Fixed altitude variance for 2D mode. (m^2)
    int8_t min_elev; // Minimum Elevation for a GNSS satellite to be used in NAV (deg)
    float p_dop; // Position DOP Mask to use
    float t_dop; // Time DOP Mask to use
    uint16_t p_acc; // Position Accuracy Mask (m)
    uint16_t t_acc; // Time Accuracy Mask (m)
    uint8_t static_hold_thres; // Static hold threshold (cm/s)
    uint8_t dgnss_timeout; // DGNSS (RTK) timeout (s)
    uint8_t cno_tres_num_sat; // Number of satellites required to have C/N0 above cnoThresh for a fix to be attempted
    uint8_t cno_tres; // C/N0 threshold for deciding whether to attempt a fix (dBHz)
    uint16_t static_hold_max_dist; // Static hold distance threshold (before quitting static hold) (m)

    /*
     * UTC standard to be used:
     * 0: Automatic; receiver selects based on GNSS configuration (see GNSS time bases).
     * 3: UTC as operated by the U.S. Naval Observatory (USNO); derived from GPS time
     * 6: UTC as operated by the former Soviet Union; derived from GLONASS time
     * 7: UTC as operated by the National Time Service Center, China; derived from BeiDou time
     */
    uint8_t utc_standard;
} ubx_cfg_nav5;

// Chronos messages

typedef enum {
    CHRONOS_MSG_DOPM = 1,
    CHRONOS_MSG_OSEM,
    CHRONOS_MSG_OSTM,
    CHRONOS_MSG_STRT,
    CHRONOS_MSG_HEAB,
    CHRONOS_MSG_MONR
} CHRONOS_MSG;

typedef struct {
    uint32_t tRel;
    double x;
    double y;
    double z;
    double heading;
    double speed;
    int16_t accel;
    int16_t curvature;
    uint8_t mode;
} chronos_dopm_pt;

typedef struct {
    double lat;
    double lon;
    double alt;
    double heading;
} chronos_osem;

typedef struct {
    bool armed;
} chronos_ostm;

typedef struct {
    uint8_t type;
    uint64_t ts;
} chronos_strt;

typedef struct {
    uint8_t status;
} chronos_heab;

typedef struct {
    uint64_t ts;
    double lat;
    double lon;
    double alt;
    double speed;
    double heading;
    uint8_t direction;
    uint8_t status;
} chronos_monr;

#endif /* DATATYPES_H_ */
