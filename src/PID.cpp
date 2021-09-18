#include "tether/PID.hpp"
#include <algorithm>

#include <chrono>
#include <cmath>

#include <math.h>


namespace tether {
    PID::PID(const std::double_t _p, const std::double_t _i, const std::double_t _d,
        const std::double_t _imax, const std::double_t _imin, const std::double_t _cmdMax,
        const std::double_t _cmdMin, const std::double_t _cmdOffset) : pGain(_p),
        iGain(_i), dGain(_d), iMax(_imax), iMin(_imin), cmdMax(_cmdMax),
        cmdMin(_cmdMin), cmdOffset(_cmdOffset) {
            Reset();
    }

    void PID::Init(const std::double_t _p, const std::double_t _i, const std::double_t _d,
                const std::double_t _imax, const std::double_t _imin, const std::double_t _cmdMax,
                const std::double_t _cmdMin, const std::double_t _cmdOffset) {
        pGain = _p;
        iGain = _i;
        iGain = _i;
        dGain = _d;
        iMax = _imax;
        iMin = _imin;
        cmdMax = _cmdMax;
        cmdMin = _cmdMin;
        cmdOffset = _cmdOffset;

        this->Reset();
    }

    PID &PID::operator=(const PID &_p) {
        if (this == &_p)
            return *this;

        pGain = _p.pGain;
        iGain = _p.iGain;
        dGain = _p.dGain;
        iMax = _p.iMax;
        iMin = _p.iMin;
        cmdMax = _p.cmdMax;
        cmdMin = _p.cmdMin;
        cmdOffset = _p.cmdOffset;
        pErrLast = _p.pErrLast;
        pErr = _p.pErr;
        iErr = _p.iErr;
        dErr = _p.dErr;
        cmd = _p.cmd;

        return *this;
    }

    void PID::SetPGain(const std::double_t _p) {
        pGain = _p;
    }

    void PID::SetIGain(const std::double_t _i) {
        iGain = _i;
    }

    void PID::SetDGain(const std::double_t _d) {
        dGain = _d;
    }

    void PID::SetIMax(const std::double_t _i) {
        iMax = _i;
    }

    void PID::SetIMin(const std::double_t _i) {
        iMin = _i;
    }

    void PID::SetCmdMax(const std::double_t _c) {
        cmdMax = _c;
    }

    void PID::SetCmdMin(const std::double_t _c) {
        cmdMin = _c;
    }

    void PID::SetCmdOffset(const std::double_t _c) {
        cmdOffset = _c;
    }

    void PID::Reset() {
        pErrLast = 0.0;
        pErr = 0.0;
        iErr = 0.0;
        dErr = 0.0;
        cmd = 0.0;
    }

    double PID::Update(const std::double_t _error, const std::chrono::duration<double> &_dt) {
        if (_dt == std::chrono::duration<double>(0) || std::isnan(_error) || std::isinf(_error)) {
            return 0.0;
        }

        double pTerm, dTerm;
        pErr = _error;

        // Calculate proportional contribution to command
        pTerm = pGain * pErr;

        // Calculate the integral error
        iErr = iErr + iGain * _dt.count() * pErr;

        // Check the integral limits
        // If enabled, this will limit iErr so that the limit is meaningful
        // in the output
        if (iMax >= iMin)
            iErr = std::clamp(iErr, iMin, iMax);

        // Calculate the derivative error
        if (_dt != std::chrono::duration<double>(0)) {
            dErr = (pErr - pErrLast) / _dt.count();
            pErrLast = pErr;
        }

        // Calculate derivative contribution to command
        dTerm = dGain * dErr;
        cmd = cmdOffset -pTerm - iErr - dTerm;

        // Check the command limits
        if (cmdMax >= cmdMin)
            cmd = std::clamp(cmd, cmdMin, cmdMax);

        return cmd;
    }

    void PID::SetCmd(const std::double_t _cmd) {
        cmd = _cmd;
    }

    double PID::Cmd() const {
        return cmd;
    }

    void PID::Errors(std::double_t &_pe, std::double_t &_ie, std::double_t &_de) const {
        _pe = pErr;
        _ie = iErr;
        _de = dErr;
    }

    double PID::PGain() const {
        return pGain;
    }

    double PID::IGain() const {
        return iGain;
    }

    double PID::DGain() const {
        return dGain;
    }

    double PID::IMax() const {
        return iMax;
    }

    double PID::IMin() const {
        return iMin;
    }

    double PID::CmdMax() const {
        return cmdMax;
    }

    double PID::CmdMin() const {
        return cmdMin;
    }

    double PID::CmdOffset() const {
        return cmdOffset;
    }
}; // namespace tether
