#include "sc_agent_calculate_set_power.hpp"

// Подключаем все необходимые заголовочные файлы для работы с sc-памятью.
#include <sc-memory/sc_memory_headers.hpp>

#include "keynodes/sc_set_keynodes.hpp"

ScAddr ScAgentCalculateSetPower::GetActionClass() const
{
  return ScSetKeynodes::action_calculate_set_power;
  // Возвращает sc-элемент по заданному идентификатору, если такой sc-элемент
  // существует в sc-памяти. Если такого sc-элемента нет, то класс агента не будет
  // зарегистрирован.
}

ScResult ScAgentCalculateSetPower::DoProgram(ScAction & action)
{
  // Получаем аргумент действия - множество, для которого необходимо посчитать мощность.
  auto const & [setAddr] = action.GetArguments<1>();
  // Если аргумент для действия не задан, то завершаем выполнение действия с ошибкой.
  if (!m_context.IsElement(setAddr))
  {
    m_logger.Error("Action does not have argument.");
    return action.FinishWithError();
  }
  // Считаем количество выходяющих базовых sc-дуг из заданного множества.
  uint32_t setPower = 0;
  ScIterator3Ptr const it3 = m_context.CreateIterator3(
    setAddr,
    ScType::ConstPermPosArc,
    ScType::ConstNode
  );
  while (it3->Next())
    ++setPower;

  // Указываем посчитанную мощность для заданного множества.
  ScAddr const & setPowerAddr = m_context.GenerateLink(ScType::ConstNodeLink);
  m_context.SetLinkContent(setPowerAddr, setPower);
  m_context.GetLinkContent(setPowerAddr, setPower);
  ScAddr const & arcCommonAddr
    = m_context.GenerateConnector(ScType::ConstCommonArc, setAddr, setPowerAddr);
  ScAddr const & membershipArcAddr = m_context.GenerateConnector(
    ScType::ConstPermPosArc,
    ScSetKeynodes::nrel_set_power,
    arcCommonAddr);
  // Добавляем всё в результат выполнения действия.
  action.FormResult(
    setAddr, 
    arcCommonAddr,
    setPowerAddr,
    membershipArcAddr, 
    ScSetKeynodes::nrel_set_power);
  m_logger.Debug("Set power was counted: ", setPower, ".");
  return action.FinishSuccessfully();
}
