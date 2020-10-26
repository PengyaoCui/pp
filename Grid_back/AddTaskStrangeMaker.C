#if !defined(__CINT__) || defined(__MAKECINT__)
#include <TList.h>
#include "AliAnalysisManager.h"
#include "AliAnalysisTaskSEStrangeMaker.h"
#endif

AliAnalysisTaskSEStrangeMaker *AddTaskStrangeMaker(const Bool_t bMC=kFALSE)
{
  AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();

  if (!mgr) {
    ::Error("AddTaskStrangeMaker::AddTaskStrangeMaker", "No analysis manager to connect to!!!");
     return NULL;
  }
//=============================================================================

  AliAnalysisTaskSEStrangeMaker *task = new AliAnalysisTaskSEStrangeMaker("AliAnaTaskSEStrangeMaker", bMC);
//=============================================================================

  mgr->AddTask(task);
  mgr->ConnectInput( task, 0, mgr->GetCommonInputContainer());
  mgr->ConnectOutput(task, 1, mgr->CreateContainer("listPicoV0MakerEH", TList::Class(), AliAnalysisManager::kOutputContainer, AliAnalysisManager::GetCommonFileName()));
  mgr->ConnectOutput(task, 1, mgr->CreateContainer("listCascadeMakerEH", TList::Class(), AliAnalysisManager::kOutputContainer, AliAnalysisManager::GetCommonFileName()));

  if (bMC) mgr->ConnectOutput(task, 2, mgr->CreateContainer("listPicoV0MakerMC", TList::Class(), AliAnalysisManager::kOutputContainer, AliAnalysisManager::GetCommonFileName()));
  if (bMC) mgr->ConnectOutput(task, 2, mgr->CreateContainer("listCascadeMakerMC", TList::Class(), AliAnalysisManager::kOutputContainer, AliAnalysisManager::GetCommonFileName()));
//=============================================================================

  return task;
}
