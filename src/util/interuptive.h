/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interuptive.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasz <tomasz@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 16:08:43 by tomasz            #+#    #+#             */
/*   Updated: 2023/05/25 18:43:36 by tomasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <esp_attr.h>

#ifndef WALLET_POC_INTERUPTIVE_H
#define WALLET_POC_INTERUPTIVE_H

#endif //WALLET_POC_INTERUPTIVE_H

class Interaptive {
public:
    static int wordIndex;
    static unsigned long lastButtonTime;

    static void (*clickPrevious())();
    static void (*clickNext())();

    static bool previousClicked();
    static bool nextClicked();
    static void begin(uint8_t previousButton, uint8_t nextButton);
    static bool isActive();
private:
    static bool _previousClicked;
    static bool _nextClicked;
    Interaptive();
};
