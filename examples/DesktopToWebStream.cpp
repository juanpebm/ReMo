/*
 * Copyright (c) 2018 CCS/UPM - GMRV/URJC.
 *
 * Authors: Juan Pedro Brito Méndez <juanpedro.brito@upm.es>
 *
 * This library is free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License version 3.0 as published
 * by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <iostream>

#include <ReMo/flow/FlowDeviceToWebStream.h>
#include <ReMo/media/MediaDesktop.h>
#include <ReMo/media/MediaWebStreamer.h>
#include <ReMo/util/Utils.h>

using namespace std;

int main ( )
{
  remo::Utils::getInstance ( )
    ->getLog ( ) ( remo::LOG_LEVEL::INFO, "Init logging." );

  //Define the input Media and Stream
  std::unique_ptr < remo::Media >
    im = std::unique_ptr < remo::MediaDesktop > ( new remo::MediaDesktop ( ));
  std::unique_ptr < remo::Stream >
    is = std::unique_ptr < remo::StreamDeviceIn > ( new remo::StreamDeviceIn
      ( im.get ( )));

  //Define the output Media and Stream
  std::unique_ptr < remo::Media > om =
    std::unique_ptr < remo::MediaWebStreamer > ( new remo::MediaWebStreamer ( ));
  std::unique_ptr < remo::Stream >
    os = std::unique_ptr < remo::StreamWebStreamer > ( new
      remo::StreamWebStreamer ( om.get ( )));

  //Define the Flow and process
  remo::FlowDeviceToWebStream f ( is.get ( ), os.get ( ));
  f.processStreams ( );

  remo::Utils::getInstance ( )->getLog ( ) ( remo::LOG_LEVEL::INFO,
                                             "Desktop viewer successfully executed." );
  return 0;
}
