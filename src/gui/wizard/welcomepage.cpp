/*
 * Copyright (C) 2021 by Felix Weilbach <felix.weilbach@nextcloud.com>
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

#include "welcomepage.h"
#include "theme.h"
#include "wizard/owncloudwizard.h"
#include "wizard/slideshow.h"
#include "ui_welcomepage.h"

namespace OCC {

WelcomePage::WelcomePage(OwncloudWizard *ocWizard)
    : QWizardPage()
    , _ui(new Ui::WelcomePage)
    , _ocWizard(ocWizard)
{
    setupUi();
}

WelcomePage::~WelcomePage() = default;

void WelcomePage::setupUi()
{
    _ui->setupUi(this);
    setupSlideShow();
    setupLoginButton();
    setupCreateAccountButton();
    setupHostYourOwnServerLabel();
}

void WelcomePage::initializePage()
{
    customizeStyle();
}

void WelcomePage::setLoginButtonDefault()
{
    _ui->loginButton->setDefault(true);
    _ui->loginButton->setFocus();
}

void WelcomePage::styleSlideShow()
{
    const auto backgroundColor = palette().window().color();
    _ui->slideShow->addSlide(Theme::hidpiFileName("wizard-nextcloud.png", backgroundColor), tr("Keep your data secure and under your control"));
    _ui->slideShow->addSlide(Theme::hidpiFileName("wizard-files.png", backgroundColor), tr("Secure collaboration & file exchange"));
    _ui->slideShow->addSlide(Theme::hidpiFileName("wizard-groupware.png", backgroundColor), tr("Easy-to-use web mail, calendaring & contacts"));
    _ui->slideShow->addSlide(Theme::hidpiFileName("wizard-talk.png", backgroundColor), tr("Screensharing, online meetings & web conferences"));

    const auto theme = Theme::instance();
    const auto isDarkBackground = Theme::isDarkColor(backgroundColor);
    _ui->slideShowNextButton->setIcon(theme->uiThemeIcon(QString("control-next.svg"), isDarkBackground));
    _ui->slideShowPreviousButton->setIcon(theme->uiThemeIcon(QString("control-prev.svg"), isDarkBackground));
}

void WelcomePage::setupSlideShow()
{
    connect(_ui->slideShow, &SlideShow::clicked, _ui->slideShow, &SlideShow::stopShow);
    connect(_ui->slideShowNextButton, &QPushButton::clicked, _ui->slideShow, &SlideShow::nextSlide);
    connect(_ui->slideShowPreviousButton, &QPushButton::clicked, _ui->slideShow, &SlideShow::prevSlide);
}

void WelcomePage::setupLoginButton()
{
    const auto appName = Theme::instance()->appNameGUI();

    _ui->loginButton->setText(tr("Log in to your %1").arg(appName));
    connect(_ui->loginButton, &QPushButton::clicked, this, [this](bool /*checked*/) {
        _nextPage = WizardCommon::Page_ServerSetup;
        _ocWizard->next();
    });
}

void WelcomePage::setupCreateAccountButton()
{
    connect(_ui->createAccountButton, &QPushButton::clicked, this, [this](bool /*checked*/) {
        _ocWizard->setRegistration(true);
        _nextPage = WizardCommon::Page_WebView;
        _ocWizard->next();
    });
}

void WelcomePage::setupHostYourOwnServerLabel()
{
    _ui->hostYourOwnServerLabel->setText(tr("Host your own server"));
    _ui->hostYourOwnServerLabel->setAlignment(Qt::AlignCenter);
    _ui->hostYourOwnServerLabel->setUrl(QUrl("https://docs.nextcloud.com/server/latest/admin_manual/installation/#installation"));
}

int WelcomePage::nextId() const
{
    return _nextPage;
}

void WelcomePage::customizeStyle()
{
    WizardCommon::customizeSecondaryButtonStyle(_ui->createAccountButton);
    WizardCommon::customizePrimaryButtonStyle(_ui->loginButton);


    styleSlideShow();
}
}
