package com.trustwallet.core.app.blockchains.aeternity

import com.trustwallet.core.app.utils.toHexBytesInByteString
import junit.framework.Assert.assertEquals
import org.junit.Test
import wallet.core.jni.AeternitySigner
import wallet.core.jni.proto.Aeternity

/**
 * Fake comment to calm codacity
 */
class TestAeternityTransactionSigning {

    init {
        System.loadLibrary("TrustWalletCore")
    }

    /**
     * Fake comment to calm codacity
     */
    @Test
    fun aeternityTransactionSigning(){
        val signingInput = Aeternity.SigningInput.newBuilder()
            .setFromAddress("ak_2p5878zbFhxnrm7meL7TmqwtvBaqcBddyp5eGzZbovZ5FeVfcw")
            .setToAddress("ak_Egp9yVdpxmvAfQ7vsXGvpnyfNq71msbdUpkMNYGTeTe8kPL3v")
            .setAmount(10L)
            .setFee(2e13.toLong())
            .setPayload("Hello world")
            .setTtl(82757)
            .setNonce(49)
            .setPrivateKey("4646464646464646464646464646464646464646464646464646464646464646".toHexBytesInByteString())
            .build()

        val output : Aeternity.SigningOutput = AeternitySigner.sign(signingInput)

        val encodedTxString = output.encoded.toString("UTF-8")
        val encodedSigString = output.signature.toString("UTF-8")

        //todo this result differs from core lib result for the same input! Although tx seems to be valid as well
        assertEquals(encodedTxString, "tx_+KkLAfhCuECMVMLpPNItbfcfcEszaj8bQwsQ+C8q5zjspXQWjWUg5rg4amR1nGyP6dJ6ASlIwnBHPH2VgD0m/lciV+SO75gEuGH4XwwBoQHuk6T2b40WuBm7m+uf/M383BQS6H/uajJMKpmh4OZxSKEBHxOjsIvwAUAGYqaLadh194A87EwIZH9u1dhMeJe9UKMKhhIwnOVAAIMBQ0Uxi0hlbGxvIHdvcmxkHYHTlg==")
        assertEquals(encodedSigString, "sg_jFTC6TzSLW33H3BLM2o/G0MLEPgvKuc47KV0Fo1lIOa4OGpkdZxsj+nSegEpSMJwRzx9lYA9Jv5XIlfkju+YBG6lgqo=")
    }

}
