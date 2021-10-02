#pragma once

#include <memory>
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
        public: int X() const;

        /// \brief The Figure y-offset
        /// \return The Figure y-offset
        public: int Y() const;

        /// \brief The Figure width
        /// \return The Figure width
        public: int Width() const;
        
        /// \brief The Figure height
        /// \return The Figure height
        public: int Height() const;

        /// \brief The figure Name
        protected: std::string m_name;

        /// \brief The Figure x-offset
        protected: int m_x = 100;

        /// \brief The Figure y-offset
        protected: int m_y = 100;
        
        /// \brief The Figure width
        protected: int m_width = 500;

        /// \brief The Figure height
        protected: int m_height = 500;
    };
} // namespace tether