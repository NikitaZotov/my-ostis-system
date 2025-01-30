// Подключаем заголовочный файл для тестирования агентов
#include <sc-memory/test/sc_test.hpp>

#include <sc-memory/sc_memory_headers.hpp>

#include "agent/sc_agent_calculate_set_power.hpp"
#include "keynodes/sc_set_keynodes.hpp"

using AgentTest = ScMemoryTest;

TEST_F(AgentTest, AgentCalculateSetPowerFinishedSuccessfully)
{
  // Регистрируем агент в sc-памяти.
  m_ctx->SubscribeAgent<ScAgentCalculateSetPower>();

  // Создаём действие с классом для выполнения агентом.
  ScAction action 
    = m_ctx->GenerateAction(ScSetKeynodes::action_calculate_set_power);

  // Создаём множество с двумя sc-элементами.
  ScSet set = m_ctx->GenerateSet();
  ScAddr nodeAddr1 = m_ctx->GenerateNode(ScType::ConstNode);
  ScAddr nodeAddr2 = m_ctx->GenerateNode(ScType::ConstNode);
  set << nodeAddr1 << nodeAddr2;

  // Устанавливаем созданное множество как аргумент для действия.
  action.SetArgument(1, set);

  // Инициируем и ждем, пока действие будет завершено.
  action.InitiateAndWait();

  // Проверяем, что действие завершилось успешно.
  EXPECT_TRUE(action.IsFinishedSuccessfully());

  // Получаем структуру результата действия.
  ScStructure structure = action.GetResult();
  // Проверяем, что она содержит sc-элементы.
  EXPECT_FALSE(structure.IsEmpty());

  // Проверяем sc-конструкции в структуре результата.
  // Проверяем первую трехэлементную конструкцию.
  ScIterator3Ptr it3 = m_ctx->CreateIterator3(
    structure, ScType::ConstPermPosArc, ScType::ConstCommonArc);
  EXPECT_TRUE(it3->Next());
  ScAddr arcAddr = it3->Get(2);

  auto [beginAddr, linkAddr] = m_ctx->GetConnectorIncidentElements(arcAddr);
  EXPECT_EQ(beginAddr, set);
  EXPECT_TRUE(m_ctx->GetElementType(linkAddr).IsLink());

  // Проверяем, что содержимое ссылки равно 2.
  uint32_t setPower;
  EXPECT_TRUE(m_ctx->GetLinkContent(linkAddr, setPower));
  EXPECT_EQ(setPower, 2u);

  // Проверяем вторую трехэлементную конструкцию.
  it3 = m_ctx->CreateIterator3(
    structure, ScType::ConstPermPosArc, ScType::ConstPermPosArc);
  EXPECT_TRUE(it3->Next());
  ScAddr arcAddr2 = it3->Get(2);

  auto [relationAddr, targetArcAddr] = m_ctx->GetConnectorIncidentElements(arcAddr2);
  EXPECT_EQ(relationAddr, ScSetKeynodes::nrel_set_power);
  EXPECT_EQ(targetArcAddr, arcAddr);

  // Дерегистрируем агент в sc-памяти.
  m_ctx->UnsubscribeAgent<ScAgentCalculateSetPower>();
}
