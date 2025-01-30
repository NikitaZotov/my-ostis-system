#include "sc_set_module.hpp"

#include "agent/sc_agent_calculate_set_power.hpp"

SC_MODULE_REGISTER(ScSetModule)
  ->Agent<ScAgentCalculateSetPower>();
  // Этот метод указывает модулю, что агент класса ScAgentCalculateSetPower
  // должен быть подписан на sc-событие добавления выходящей sc-дуги из 
  // sc-элемента action_initiated.

// Такой способ подписки агентов упрощает написание кода. 
// Вам не нужно думать об отписке агентов после 
// выключения системы - ваш модуль сделает это сам.
