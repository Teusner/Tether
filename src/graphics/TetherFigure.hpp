#pragma once

#include <cmath>
#include <string>

namespace tether {

    class TetherFigure {
        public: TetherFigure(std::string name = "") : m_name(name) {};
        public: ~TetherFigure() = default;

        /// \brief The Figure name
        /// \return The Figure name
        public: std::string Name() const;

        /// \brief The Figure x-offset
        /// \return The Figure x-offset
        public: std::double_t X() const;

        /// \brief The Figure y-offset
        /// \return The Figure y-offset
        public: std::double_t Y() const;

        /// \brief The Figure width
        /// \return The Figure width
        public: std::double_t Width() const;
        
        /// \brief The Figure height
        /// \return The Figure height
        public: std::double_t Height() const;

        /// \brief The figure Name
        private: std::string m_name;

        /// \brief The Figure x-offset
        private: std::size_t m_x = 100;

        /// \brief The Figure y-offset
        private: std::size_t m_y = 100;
        
        /// \brief The Figure width
        private: std::size_t m_width = 500;

        /// \brief The Figure height
        private: std::size_t m_height = 500;
}