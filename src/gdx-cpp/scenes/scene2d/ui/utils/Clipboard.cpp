
/*
    Copyright 2011 Aevum Software aevum @ aevumlab.com

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.

    @author Victor Vicente de Carvalho victor.carvalho@aevumlab.com
    @author Ozires Bortolon de Faria ozires@aevumlab.com
*/

#include "Clipboard.hpp"

using namespace gdx_cpp::scenes::scene2d::ui::utils;

Clipboard& Clipboard::getDefaultClipboard () {
    if (Gdx.app.getType() == ApplicationType.Android)
        return new AndroidClipboard();
    else {
        try {
            return (Clipboard)(Class.forName("com.badlogic.gdx.scenes.scene2d.ui.utils.DesktopClipboard").newInstance());
        } catch (Exception e) {
            throw new GdxRuntimeException("Couldn't instantiate desktop clipboard", e);
        }
    }
}

