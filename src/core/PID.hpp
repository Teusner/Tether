/// \file PID.hpp
/// Implementation of a PID controller

#pragma once

#include <chrono>
#include <math.h>

namespace tether {
    /// \class PID PID.hpp tether/PID.hpp
    /// \brief Generic PID controller class.
    /// Generic proportional-integral-derivative controller class that
    /// keeps track of PID-error states and control inputs given
    /// the state of a system and a user specified target state.
    /// It includes a user-adjustable command offset term (feed-forward).
    class PID {
        /// \brief Constructor, zeros out Pid values when created and
        /// initialize Pid-gains and integral term limits:[iMax:iMin]-[I1:I2].
        ///
        /// Disable command clamping by setting _cmdMin to a value larger
        /// than _cmdMax. Command clamping is disabled by default.
        ///
        /// Disable integral clamping by setting _iMin to a value larger
        /// than _iMax. Integral clamping is disabled by default.
        ///
        /// \param[in] _p  The proportional gain.
        /// \param[in] _i  The integral gain.
        /// \param[in] _d  The derivative gain.
        /// \param[in] _imax The integral upper limit.
        /// \param[in] _imin The integral lower limit.
        /// \param[in] _cmdMax Output max value.
        /// \param[in] _cmdMin Output min value.
        /// \param[in] _cmdOffset Command offset (feed-forward).
        public: PID(const std::double_t _p = 0.0,
                    const std::double_t _i = 0.0,
                    const std::double_t _d = 0.0,
                    const std::double_t _imax = -1.0,
                    const std::double_t _imin = 0.0,
                    const std::double_t _cmdMax = -1.0,
                    const std::double_t _cmdMin = 0.0,
                    const std::double_t _cmdOffset = 0.0);

        /// \brief Destructor
        public: ~PID() = default;

        /// \brief Initialize PID-gains and integral term
        ///        limits:[iMax:iMin]-[I1:I2].
        ///
        /// Disable command clamping by setting _cmdMin to a value larger
        /// than _cmdMax. Command clamping is disabled by default.
        ///
        /// Disable integral clamping by setting _iMin to a value larger
        /// than _iMax. Integral clamping is disabled by default.
        ///
        /// \param[in] _p  The proportional gain.
        /// \param[in] _i  The integral gain.
        /// \param[in] _d  The derivative gain.
        /// \param[in] _imax The integral upper limit.
        /// \param[in] _imin The integral lower limit.
        /// \param[in] _cmdMax Output max value.
        /// \param[in] _cmdMin Output min value.
        /// \param[in] _cmdOffset Command offset (feed-forward).
        public: void Init(const std::double_t _p = 0.0,
                            const std::double_t _i = 0.0,
                            const std::double_t _d = 0.0,
                            const std::double_t _imax = -1.0,
                            const std::double_t _imin = 0.0,
                            const std::double_t _cmdMax = -1.0,
                            const std::double_t _cmdMin = 0.0,
                            const std::double_t _cmdOffset = 0.0);

        /// \brief Set the proportional Gain.
        /// \param[in] _p proportional gain value
        public: void SetPGain(const std::double_t _p);

        /// \brief Set the integral Gain.
        /// \param[in] _i integral gain value
        public: void SetIGain(const std::double_t _i);

        /// \brief Set the derivtive Gain.
        /// \param[in] _d derivative gain value
        public: void SetDGain(const std::double_t _d);

        /// \brief Set the integral upper limit.
        /// \param[in] _i integral upper limit value
        public: void SetIMax(const std::double_t _i);

        /// \brief Set the integral lower limit.
        /// \param[in] _i integral lower limit value
        public: void SetIMin(const std::double_t _i);

        /// \brief Set the maximum value for the command.
        /// \param[in] _c The maximum value
        public: void SetCmdMax(const std::double_t _c);

        /// \brief Set the minimum value for the command.
        /// \param[in] _c The minimum value
        public: void SetCmdMin(const std::double_t _c);

        /// \brief Set the offset value for the command,
        /// which is added to the result of the PID controller.
        /// \param[in] _c The offset value
        public: void SetCmdOffset(const std::double_t _c);

        /// \brief Get the proportional Gain.
        /// \return The proportional gain value
        public: double PGain() const;

        /// \brief Get the integral Gain.
        /// \return The integral gain value
        public: double IGain() const;

        /// \brief Get the derivative Gain.
        /// \return The derivative gain value
        public: double DGain() const;

        /// \brief Get the integral upper limit.
        /// \return The integral upper limit value
        public: double IMax() const;

        /// \brief Get the integral lower limit.
        /// \return The integral lower limit value
        public: double IMin() const;

        /// \brief Get the maximum value for the command.
        /// \return The maximum value
        public: double CmdMax() const;

        /// \brief Get the maximum value for the command.
        /// \return The maximum value
        public: double CmdMin() const;

        /// \brief Get the offset value for the command.
        /// \return The offset value
        public: double CmdOffset() const;

        /// \brief Update the Pid loop with nonuniform time step size.
        /// \param[in] _error  Error since last call (p_state - p_target).
        /// \param[in] _dt Change in time since last update call.
        /// Normally, this is called at every time step,
        /// The return value is an updated command to be passed
        /// to the object being controlled.
        /// \return the command value
        public: double Update(const std::double_t _error,
                                const std::chrono::duration<double> &_dt);

        /// \brief Set current target command for this PID controller.
        /// \param[in] _cmd New command
        public: void SetCmd(const double _cmd);

        /// \brief Return current command for this PID controller.
        /// \return the command value
        public: double Cmd() const;

        /// \brief Return PID error terms for the controller.
        /// \param[in] _pe  The proportional error.
        /// \param[in] _ie  The integral of gain times error.
        /// \param[in] _de  The derivative error.
        public: void Errors(std::double_t &_pe, std::double_t &_ie, std::double_t &_de) const;

        /// \brief Assignment operator
        /// \param[in] _p a reference to a PID to assign values from
        /// \return reference to this instance
        public: PID &operator=(const PID &_p);

        /// \brief Reset the errors and command.
        public: void Reset();

        /// \brief Error at a previous step.
        private: double pErrLast = 0.0;

        /// \brief Current error.
        private: double pErr = 0.0;

        /// \brief Integral of gain times error.
        private: double iErr = 0.0;

        /// \brief Derivative error.
        private: double dErr = 0.0;

        /// \brief Gain for proportional control.
        private: double pGain;

        /// \brief Gain for integral control.
        private: double iGain = 0.0;

        /// \brief Gain for derivative control.
        private: double dGain = 0.0;

        /// \brief Maximum clamping value for integral term.
        private: double iMax = -1.0;

        /// \brief Minim clamping value for integral term.
        private: double iMin = 0.0;

        /// \brief Command value.
        private: double cmd = 0.0;

        /// \brief Max command clamping value.
        private: double cmdMax = -1.0;

        /// \brief Min command clamping value.
        private: double cmdMin = 0.0;

        /// \brief Command offset.
        private: double cmdOffset = 0.0;
    };
}; // namespace tether
