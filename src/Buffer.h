#pragma once

#include "interfaces.h"

class Buffer : public Bindable
{
  protected:
    Microsoft::WRL::ComPtr<ID3D11Buffer> pBuffer;
};
