/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seed.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tomasz <tomasz@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:22:08 by tomasz            #+#    #+#             */
/*   Updated: 2023/05/25 15:50:31 by tomasz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bip39/word_list.h"

#ifndef WALLET_POC_SEED_H
#define WALLET_POC_SEED_H

#endif //WALLET_POC_SEED_H

class Seed
{
public:
    static BIP39::word_list createMnemonic();

private:
    // LightState here is now a class, not the enum that we saw earlier
    Seed();
    static void generateEntropy();
    static std::vector<uint8_t> entropy;
};
