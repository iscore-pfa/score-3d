/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "logo.h"
#include <qmath.h>

Logo::Logo()
    : m_count(0)
{
    m_data.resize(2500 * 6);

    int nb_point = 4;

    GLfloat tab[nb_point][3];
    tab[0][0] = 0.0f;
    tab[0][1] = 0.0f;
    tab[0][2] = 0.0f;

    tab[1][0] = 0.5f;
    tab[1][1] = 0.0f;
    tab[1][2] = 0.0f;

    tab[2][0] = 0.5f;
    tab[2][1] = 0.5f;
    tab[2][2] = 0.0f;

    tab[3][0] = 0.0f;
    tab[3][1] = 0.5f;
    tab[3][2] = 0.0f;

    quad(tab,nb_point);
}

void Logo::add(const QVector3D &v, const QVector3D &n)
{
    GLfloat *p = m_data.data() + m_count;
    *p++ = v.x();
    *p++ = v.y();
    *p++ = v.z();
    *p++ = n.x();
    *p++ = n.y();
    *p++ = n.z();
    m_count += 6;
}

void Logo::quad(const GLfloat (*tab)[3], int length) //Idée possible faire des fonctions distinctes pour reliers tous les points d'un tableau ensemble
                                                     // ou les un après les autres comme ça plus simple pour dessiner forme 3d
{
    QVector3D n = QVector3D::normal(QVector3D(0, 0, 0), QVector3D(0, 0, 0));

//    for(int i = 0; i < length; i++){ // Relis tous les points ensembles
//        for(int j = i; j < length; j++){
//            add(QVector3D(tab[i][0], tab[i][1], tab[i][2]), n); // Toujours faire par paire (Fais un trait en le point 1 et 2)
//            add(QVector3D(tab[j][0], tab[j][1], tab[j][2]), n);
//        }
//    }

    for(int i = 0; i < length-1; i++){ // Relis les points par ordre d'apparition
        add(QVector3D(tab[i][0], tab[i][1], tab[i][2]), n); // Toujours faire par paire (Fais un trait en le point 1 et 2)
        add(QVector3D(tab[i+1][0], tab[i+1][1], tab[i+1][2]), n);
    }
    add(QVector3D(tab[length-1][0], tab[length-1][1], tab[length-1][2]), n);
    add(QVector3D(tab[0][0], tab[0][1], tab[0][2]), n);
}
