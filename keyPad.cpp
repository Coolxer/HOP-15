#include "keyPad.h"

KeysController::KeysController()
{
 
}

char KeysController::getPushedKey()
{
  return m_keyPad.getKey();
}

