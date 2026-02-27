#pragma once

#include "InputUtility.hpp"

namespace banana
{
    class GameController
    {
        public:
            GameController();
            GameController(id_t deviceIndex);
            ~GameController();

            void updatAxis(SDL_GameControllerAxis axis, float value);
            void updateButton(SDL_GameControllerButton, bool pressed);
            void rumble(float strength, uint32_t ms);
            void disconect();

            GameControllerButtonStates getButton(GameControllerButtons button) const;
            float getAxis(GameControllerAxis axis) const;

            bool getConnection() const;

            GameControllerBrand getBrand() const;

            SDL_GameController* getHandle();
        
        private:
            SDL_GameController* m_Controller;

            bool m_Connected;

            GameControllerBrand m_Brand;

            std::array<float, static_cast<id_t>(GameControllerAxis::COUNT)> m_Axis;
            std::array<GameControllerButtonStates, static_cast<id_t>(GameControllerButtons::COUNT)> m_Buttons;

            void initValues();

            id_t fromSDL(SDL_GameControllerAxis axis) const;
            id_t fromSDL(SDL_GameControllerButton button) const;
            GameControllerBrand fromSDL(SDL_GameControllerType brand) const;
    };
}