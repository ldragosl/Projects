#include "ObiectStaticNormale.h"

#include <GL/glew.h>

void ObiectStaticNormale::randare()
{
	if (esteUtilizabila()) {
		// informam openGL ca vor fii transmise catre shadere 5 atribute
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glEnableVertexAttribArray(3);
		glEnableVertexAttribArray(4);

		//ordinea atributelor este aceeasi cu cea in care au fost declarate atributele in vertex shader

		//coordonatele punctelor 3D
		glBindBuffer(GL_ARRAY_BUFFER, bufferPuncte3D);
		glVertexAttribPointer(
			0,                  // nr atribut
			3,                  // numarul de componente al fiecarei coordonate 3D
			GL_FLOAT,           // tipul datelor din buffer
			GL_FALSE,           // datele nu sunt normalizate
			0,                  // stride - 0 deoarece vom randa toate punctele din buffer
			NULL				// array buffer offset
		);

		//bufferul de coordonate UV (maparea suprafetelor 3D la texturi 2D)
		glBindBuffer(GL_ARRAY_BUFFER, bufferUV);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);
		//normalele
		glBindBuffer(GL_ARRAY_BUFFER, bufferNormale);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		// tangentele
		glBindBuffer(GL_ARRAY_BUFFER, bufferTangente);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 0, NULL);
		// bitangentele
		glBindBuffer(GL_ARRAY_BUFFER, bufferBitangente);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, 0, NULL);


		// transmitem OpenGL indecsii punctelor ce alcatuiesc triunghiurile ce urmeaza a fii randate
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bufferTriunghiuri);

		// cerem OpenGL sa rendeze obiectul utilizand shaderele selectate si informatia buffer-uita
		glDrawElements(
			GL_TRIANGLES,							// modul de randare
			numarPuncte,	//numarul de varfuri de triunghi (nr triunghiuri * 3)
			GL_UNSIGNED_INT,						//tipul indecsilor este int
			NULL									// nu avem offset
		);

		//materialul a fost randat: curatam atributele utilizate pentru a putea randa alte shadere
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glDisableVertexAttribArray(3);
		glDisableVertexAttribArray(4);
	}
}

ObiectStaticNormale::ObiectStaticNormale()
{
	bufferNormale = 0;
	bufferTangente = 0;
	bufferBitangente = 0;
}
