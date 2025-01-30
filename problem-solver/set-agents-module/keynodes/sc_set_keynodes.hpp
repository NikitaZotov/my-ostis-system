#include <sc-memory/sc_keynodes.hpp>

// Создаём класс, объединяющий ключевые sc-элементы, используемые агентами 
// в рамках одного модуля.
// Наследуем его от базового класса ScKeynodes.
class ScSetKeynodes : public ScKeynodes
{
public:
  static inline ScKeynode const action_calculate_set_power{
    "action_calculate_set_power", ScType::ConstNodeClass};
  static inline ScKeynode const nrel_set_power{
    "nrel_set_power", ScType::ConstNodeNonRole};
  // Здесь первым аргументом конструктора является системный идентификатор 
  // ключевого sc-элемента, а второй аргумент - тип этого sc-элемента.
  // Если в sc-памяти нет ключевого sc-элемента с таким системным идентификатором,
  // то в ней будет создан sc-элемент с таким системным идентификатором 
  // и указанным типом.
};
