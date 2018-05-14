#include "PID.h"
#include<iostream>
using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {

    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    best_err= std::numeric_limits<double>::max();
}

void PID::UpdateError(double cte) {
    d_error = cte - p_error;
    p_error = cte;
    i_error += cte;
}

double PID::TotalError() {
    return (-Kp * p_error - Ki * i_error - Kd * d_error);

}


double PID::TwiddleError(double p [])  {
    double foo = -p[0]*p_error - p[1]*i_error - p[2]*d_error;
    return (err + foo*foo)/n;
}

void PID::Twiddle() {
    double tol = 0.2;
    dp[0] = Kp / 10.0;
    dp[1] = 0.0;
    dp[2] = Kd / 10.0;
    int i = 0;
    double p[3];
    p[0] = Kp;
    p[1] = Ki;
    p[2] = Kd;
    best_err = TwiddleError(p);

    while (dp[0] + dp[1] + dp[2] > tol) {
        cout << "Twiddle iteration " << i << ", best error = " << best_err << endl;
        cout << "Kp " << p[0] << ", Ki " << p[1] << ", Kd " << p[2] << endl;
        cout << "dKp " << dp[0] << ", dKi " << dp[1] << ", dKd " << dp[2] << endl;
        for (int j = 0; j < 3; ++j) {
            p[j] += dp[j];
            double error = TwiddleError(p);

            if (error*error < best_err) {
                best_err = error*error;
                dp[j] *= 1.1;
            } else {
                p[j] -= 2 * dp[j];
                error = TwiddleError(p);

                if (error*error < best_err) {
                    best_err = error*error;
                    dp[j] *= 1.1;
                } else {
                    p[j] += dp[j];
                    dp[j] *= 0.9;
                }
            }
        }
        i++;
    }
    Kp = p[0];
    Ki = p[1];
    Kd = p[2];
}