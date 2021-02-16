/*
 * Copyright (C) by Klaas Freitag <freitag@owncloud.com>
 * Copyright (C) by Krzesimir Nowak <krzesimir@endocode.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 */

#include <QLabel>
#include <QPixmap>
#include <QVariant>
#include <QRadioButton>
#include <QAbstractButton>
#include <QCheckBox>
#include <QSpinBox>

#include "wizard/owncloudwizardcommon.h"
#include "theme.h"

namespace OCC {

namespace WizardCommon {

    void setupCustomMedia(const QVariant &variant, QLabel *label)
    {
        if (!label)
            return;

        QPixmap pix = variant.value<QPixmap>();
        if (!pix.isNull()) {
            label->setPixmap(pix);
            label->setAlignment(Qt::AlignTop | Qt::AlignRight);
            label->setVisible(true);
        } else {
            QString str = variant.toString();
            if (!str.isEmpty()) {
                label->setText(str);
                label->setTextFormat(Qt::RichText);
                label->setVisible(true);
                label->setOpenExternalLinks(true);
            }
        }
    }

    QString titleTemplate()
    {
        return QString::fromLatin1(R"(<font color="%1" size="5">)").arg(Theme::instance()->wizardHeaderTitleColor().name()) + QString::fromLatin1("%1</font>");
    }

    QString subTitleTemplate()
    {
        return QString::fromLatin1("<font color=\"%1\">").arg(Theme::instance()->wizardHeaderTitleColor().name()) + QString::fromLatin1("%1</font>");
    }

    void initErrorLabel(QLabel *errorLabel)
    {
        QString style = QLatin1String("border: 1px solid #eed3d7; border-radius: 5px; padding: 3px;"
                                      "background-color: #f2dede; color: #b94a48;");

        errorLabel->setStyleSheet(style);
        errorLabel->setWordWrap(true);
        auto sizePolicy = errorLabel->sizePolicy();
        sizePolicy.setRetainSizeWhenHidden(true);
        errorLabel->setSizePolicy(sizePolicy);
        errorLabel->setVisible(false);
    }

    void customizeSpinBoxStyle(QSpinBox *spinBox)
    {
        auto spinBoxPalette = spinBox->palette();
#ifdef Q_OS_WIN
        // Windows always uses a SpinBox with a white background but we change the color of the text so we need
        // to change the text color here
        spinBoxPalette.setColor(QPalette::Text, Qt::black);
        QColor colorTextDisabled(spinBoxPalette.color(QPalette::Text));
        colorTextDisabled.setAlpha(128);
        spinBoxPalette.setColor(QPalette::Disabled, QPalette::Text, colorTextDisabled);
#endif
#ifdef Q_OS_LINUX
        spinBoxPalette.setColor(QPalette::WindowText, Theme::instance()->wizardHeaderBackgroundColor());
        QColor colorWindowTextDisabled(spinBoxPalette.color(QPalette::WindowText));
        colorWindowTextDisabled.setAlpha(128);
        spinBoxPalette.setColor(QPalette::Disabled, QPalette::WindowText, colorWindowTextDisabled);
#endif
        spinBox->setPalette(spinBoxPalette);
    }

    void customizeSecondaryButtonStyle(QAbstractButton *button)
    {
#ifdef Q_OS_LINUX
        // Only style push buttons on Linux as on other platforms we are unable to style the background color
        auto pushButtonPalette = button->palette();
        pushButtonPalette.setColor(QPalette::ButtonText, Theme::instance()->wizardHeaderTitleColor());
        pushButtonPalette.setColor(QPalette::Button, Theme::instance()->wizardHeaderBackgroundColor());
        button->setPalette(pushButtonPalette);
#else
        Q_UNUSED(button);
#endif
    }

    void customizeLinkButtonStyle(QAbstractButton *button)
    {
        auto buttonPalette = button->palette();
        buttonPalette.setColor(QPalette::ButtonText, Theme::instance()->wizardHeaderTitleColor());
        button->setPalette(buttonPalette);
    }

    void customizePrimaryButtonStyle(QAbstractButton *button)
    {
#ifdef Q_OS_LINUX
        // Only style push buttons on Linux as on other platforms we are unable to style the background color
        auto pushButtonPalette = button->palette();

        pushButtonPalette.setColor(QPalette::Button, Theme::instance()->wizardHeaderTitleColor());
        auto disabledButtonColor = pushButtonPalette.color(QPalette::Button);
        disabledButtonColor.setAlpha(128);
        pushButtonPalette.setColor(QPalette::Disabled, QPalette::Button, disabledButtonColor);

        pushButtonPalette.setColor(QPalette::ButtonText, Theme::instance()->wizardHeaderBackgroundColor());
        auto disabledButtonTextColor = pushButtonPalette.color(QPalette::ButtonText);
        disabledButtonTextColor.setAlpha(128);
        pushButtonPalette.setColor(QPalette::Disabled, QPalette::ButtonText, disabledButtonTextColor);

        button->setPalette(pushButtonPalette);
#else
        Q_UNUSED(button);
#endif
    }

    void customizeHintLabel(QLabel *label)
    {
        QColor textColor(Theme::instance()->wizardHeaderTitleColor());
        textColor.setAlpha(128);

        auto palette = label->palette();
        palette.setColor(QPalette::Text, textColor);
        label->setPalette(palette);
    }

} // ns WizardCommon

} // namespace OCC
