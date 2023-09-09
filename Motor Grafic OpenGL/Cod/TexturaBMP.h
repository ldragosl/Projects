
#include "Interfete\Textura.h"

class TexturaBMP : public Textura
{
public:
    TexturaBMP(std::string caleFisier);
    ~TexturaBMP();

    virtual void initializeazaResursa() override;
    virtual void elibereazaMemorie() override;

protected:
    virtual void incarcaResursa() override;
private:
    unsigned int latime;
    unsigned int inaltime;
    char* informatieRGB;
};
