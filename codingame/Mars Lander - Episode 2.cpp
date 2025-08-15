#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

static int clampInt(int v, int lo, int hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

static double clampDouble(double v, double lo, double hi) {
    if (v < lo) return lo;
    if (v > hi) return hi;
    return v;
}

int main() {
    int surfaceN;
    cin >> surfaceN; cin.ignore();
    vector<pair<int,int>> points(surfaceN);
    for (int i = 0; i < surfaceN; i++) {
        cin >> points[i].first >> points[i].second; cin.ignore();
    }

    int flatY = 0;
    int flatLeftX = 0;
    int flatRightX = 0;
    for (int i = 1; i < surfaceN; i++) {
        if (points[i].second == points[i - 1].second) {
            flatY = points[i].second;
            flatLeftX = min(points[i].first, points[i - 1].first);
            flatRightX = max(points[i].first, points[i - 1].first);
            break;
        }
    }
    int targetX = (flatLeftX + flatRightX) / 2;
    cerr << "flatY=" << flatY << " leftX=" << flatLeftX << " rightX=" << flatRightX << " targetX=" << targetX << endl;

    while (true) {
        int x, y, hSpeed, vSpeed, fuel, rotate, power;
        cin >> x >> y >> hSpeed >> vSpeed >> fuel >> rotate >> power; cin.ignore();

        int altitude = y - flatY;
        bool overZone = (flatLeftX <= x && x <= flatRightX);
        int distX = targetX - x;

        int maxH = 20;
        if (!overZone) {
            int dxToZone = x < flatLeftX ? (flatLeftX - x) : (x - flatRightX);
            if (dxToZone > 1800) maxH = 70;
            else if (dxToZone > 1200) maxH = 60;
            else if (dxToZone > 700) maxH = 50;
            else if (dxToZone > 300) maxH = 40;
            else maxH = 30;
        } else {
            if (altitude > 2000) maxH = 60;
            else if (altitude > 1200) maxH = 45;
            else if (altitude > 800) maxH = 35;
            else if (altitude > 400) maxH = 25;
            else maxH = 18;
        }

        int desiredHSpeed = 0;
        if (!overZone) desiredHSpeed = (distX > 0 ? maxH : -maxH);
        else desiredHSpeed = 0;

        double axMax = 1.8;
        double brakeDist = (double)abs(hSpeed) * (double)abs(hSpeed) / (2.0 * axMax) + 300.0;
        bool needBrake = (!overZone && (double)abs(distX) <= brakeDist);
        if (needBrake) desiredHSpeed = 0;

        double speedError = static_cast<double>(desiredHSpeed - hSpeed);
        int pdAngle = clampInt(static_cast<int>(speedError * -0.7), -45, 45);
        int rawAngle = pdAngle;

        int stepsToZero = (abs(rotate) + 14) / 15;
        int straightenAlt = 180 + 60 * stepsToZero;

        int maxTilt = 45;
        if (vSpeed <= -60) maxTilt = 20;
        else if (vSpeed <= -50) maxTilt = 30;
        if (altitude < 1000) maxTilt = min(maxTilt, 25);
        if (altitude < 400) maxTilt = min(maxTilt, 15);

        if (altitude < 200) rawAngle = 0;
        if (overZone) {
            if (altitude < 800) maxTilt = min(maxTilt, 10);
            if (abs(hSpeed) <= 22) rawAngle = 0;
        }
        rawAngle = clampInt(rawAngle, -maxTilt, maxTilt);

        int targetV = -35;
        if (altitude > 2500) targetV = -60;
        else if (altitude > 1800) targetV = -55;
        else if (altitude > 1200) targetV = -50;
        else if (altitude > 900) targetV = -42;
        else if (altitude > 700) targetV = -40;
        else if (altitude > 500) targetV = -38;
        else if (altitude > 300) targetV = -35;
        else if (altitude > 120) targetV = -30;
        else if (altitude > 60) targetV = -25;
        else targetV = -20;

        if (!overZone) {
            int dxToZone = x < flatLeftX ? (flatLeftX - x) : (x - flatRightX);
            int tv = -30;
            if (dxToZone > 1500) tv = -30;
            else if (dxToZone > 800) tv = -35;
            else if (dxToZone > 400) tv = -35;
            else if (dxToZone > 200) tv = -30;
            if (altitude < 700 && tv > -35) tv = -30;
            targetV = max(targetV, tv);
        }
        if (targetV < vSpeed) targetV = vSpeed;

        const double g = 3.711;
        const double PI = 3.141592653589793;
        double angleRad = fabs(rawAngle) * PI / 180.0;
        double cosA = cos(angleRad);
        if (cosA < 0.15) cosA = 0.15;
        double dv = static_cast<double>(targetV - vSpeed);
        double desiredAccY = clampDouble(dv, -2.0, 3.0);
        double desiredPowerD = (desiredAccY + g) / cosA;
        int rawPower = clampInt((int)lround(desiredPowerD), 0, 4);

        if (altitude < 80) rawPower = max(rawPower, 3);

        int nextAngle = rawAngle;
        if (nextAngle > rotate + 15) nextAngle = rotate + 15;
        if (nextAngle < rotate - 15) nextAngle = rotate - 15;
        nextAngle = clampInt(nextAngle, -90, 90);

        int nextPower = rawPower;
        if (nextPower > power + 1) nextPower = power + 1;
        if (nextPower < power - 1) nextPower = power - 1;
        nextPower = clampInt(nextPower, 0, 4);

        cerr << "pos=(" << x << "," << y << ") hs=" << hSpeed << " vs=" << vSpeed
             << " fuel=" << fuel << " rot=" << rotate << " pow=" << power
             << " alt=" << altitude << " over=" << (overZone?1:0) << " distX=" << distX
             << " maxH=" << maxH << " desHS=" << desiredHSpeed
             << " pdA=" << pdAngle << " steps0=" << stepsToZero << " strAlt=" << straightenAlt << " brakeD=" << (int)brakeDist << " needBr=" << (needBrake?1:0) << " maxTilt=" << maxTilt
             << " rawA=" << rawAngle << " tV=" << targetV << " dv=" << (targetV - vSpeed)
             << " accY=" << desiredAccY << " cosA=" << cosA << " rPow=" << rawPower
             << " out=(" << nextAngle << "," << nextPower << ")" << endl;
        cout << nextAngle << " " << nextPower << endl;
    }
}