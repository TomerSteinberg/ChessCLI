#include "InvalidPromotionException.h"

InvalidPromotionException::InvalidPromotionException()
{
    this->errMsg = "Invalid Promotion: You can only promote to Knight, Bishop, Rook or Queen\n";
}

const char* InvalidPromotionException::what() const noexcept
{
    return nullptr;
}
