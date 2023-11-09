
#include "beam_view.h"



    // BeamDTO beam;
    // Texture& beamTexture;


BeamView::BeamView(BeamDTO& beam, Texture& beamSprite) : beam(beam), beamSprite(beamSprite) {}

BeamView::~BeamView() {}

void BeamView::display(Renderer& renderer, int camX, int camY) {
    renderer.Copy(
        this->beamSprite,
        Rect(0,0,140,20),
        Rect(((int )beam.getPosition().getX() * m_to_pix_x )-camX, ((int )beam.getPosition().getY() * m_to_pix_y + WINDOW_HEIGHT) -camY, beam.getBeamLength() * m_to_pix_x, -0.8 * m_to_pix_y), //deberia hacerlo en preprocess pero no es parte de beam y es algo temporal
        (- beam.getAngle()), Point(0, 0)
    );

    // std::cout << beam.getPosition().getX() << std::endl;
    // std::cout << beam.getBeamLength() << std::endl;
}
