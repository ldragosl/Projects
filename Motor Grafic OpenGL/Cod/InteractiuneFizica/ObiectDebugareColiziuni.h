#pragma once
#include "ObiectStatic.h"

//singleton
class ObiectDebugareColiziuni : public ObiectStatic{
private:
    static ObiectDebugareColiziuni* referintaSingleton;
    ObiectDebugareColiziuni();
    ~ObiectDebugareColiziuni();
    virtual void incarcaResursa() override;
    virtual void initializeazaResursa() override;
    void elibereazaMemorie();
    std::vector< int > indiciTriunghiuri;
public:
    static ObiectDebugareColiziuni* obtineObiectDebugareColiziuni();

    void reimprospatare();

    virtual void randare() override;
};

