#include "GameController.hpp"

namespace banana
{
    GameController::GameController()
    {
        //shoudld never be used, here for compiler purposes
        BANANA_FATAL("Game Controller not correctly created!");
    }

    GameController::GameController(id_t deviceIndex)
    {
        //check if device is a game controller
        if(!SDL_IsGameController(deviceIndex))
        {
            BANANA_ERROR("Device at index {} not recognised!", deviceIndex);
            return;
        }

        //add game controller
        m_Controller = SDL_GameControllerOpen(deviceIndex);
        if (!m_Controller)
        {
            m_Controller = nullptr;
            BANANA_ERROR("Could not open game controller at index {}: {}", deviceIndex, SDL_GetError());
            return;
        }

        m_Connected = true;

        m_Brand = fromSDL(SDL_GameControllerGetType(m_Controller));
        BANANA_INFO("Opened a Game controller at index {}!", deviceIndex);
        initValues();
    }

    GameController::~GameController()
    {
        if(m_Controller)
            SDL_GameControllerClose(m_Controller);
        m_Controller = nullptr;

        BANANA_INFO("Closed a Game controller!");
    }

    void GameController::updatAxis(SDL_GameControllerAxis axis, float value)
    {
        m_Axis[fromSDL(axis)] = value;
    }

    void GameController::updateButton(SDL_GameControllerButton button, bool pressed)
    {
        m_Buttons[fromSDL(button)] = pressed ? GameControllerButtonStates::PRESSED : GameControllerButtonStates::RELEASED;
    }

    void GameController::rumble(float strength, uint32_t ms)
    {
        uint16_t s = static_cast<uint16_t>(strength * 0xFFFF);
        SDL_GameControllerRumble(m_Controller, s, s, ms);
    }

    SDL_GameController* GameController::getHandle()
    {
        return m_Controller;
    }

    GameControllerButtonStates GameController::getButton(GameControllerButtons button) const
    {
        return m_Buttons[static_cast<id_t>(button)];
    }

    float GameController::getAxis(GameControllerAxis axis) const
    {
        return m_Axis[static_cast<id_t>(axis)];
    }

    bool GameController::getConnection() const
    {
        return m_Connected;
    }

    GameControllerBrand GameController::getBrand() const
    {
        return m_Brand;
    }

    void GameController::initValues()
    {
        for(id_t i = 0; i < static_cast<id_t>(GameControllerAxis::COUNT); i++)
        {
            m_Axis[i] = 0.0f;
        }

        if(m_Brand == GameControllerBrand::Xbox360 || m_Brand == GameControllerBrand::XboxOne)
        {
            m_Axis[static_cast<id_t>(GameControllerAxis::LeftT)] = 1.0f;
            m_Axis[static_cast<id_t>(GameControllerAxis::RightT)] = 1.0f;
        }

        for(id_t i = 0; i < static_cast<id_t>(GameControllerButtons::COUNT); i++)
        {
            m_Buttons[i] = GameControllerButtonStates::RELEASED;
        }
    }

    void GameController::disconect()
    {
        m_Connected = false;

        //init values so if user checks it it can be null
        initValues();
    }

    id_t GameController::fromSDL(SDL_GameControllerAxis axis) const
    {
        auto iterator = GAMECONTROLLERAXISMAP.find(axis);

        if(iterator != GAMECONTROLLERAXISMAP.end())
            return static_cast<id_t>(iterator->second);
        return static_cast<id_t>(GameControllerAxis::UNKNOWN);
    }

    id_t GameController::fromSDL(SDL_GameControllerButton button) const
    {
        auto iterator = GAMECONTROLLERBUTTOMMAP.find(button);

        if(iterator != GAMECONTROLLERBUTTOMMAP.end())
            return static_cast<id_t>(iterator->second);
        return static_cast<id_t>(GameControllerButtons::UNKNOWN);
    }

    GameControllerBrand GameController::fromSDL(SDL_GameControllerType brand) const
    {
        auto iterator = GAMECONTROLLERBRANDMAP.find(brand);

        if(iterator != GAMECONTROLLERBRANDMAP.end())
            return iterator->second;
        return GameControllerBrand::UNKNOWN;
    }
}