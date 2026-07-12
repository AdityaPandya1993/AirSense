//
//  ASSerialDelegate.swift
//  AirSense
//
//  Created by ADITYA PANDYA on 12/07/26.
//


import Foundation

protocol ASSerialDelegate: AnyObject
{
    func serialManagerDidConnect()

    func serialManagerDidDisconnect()

    func serialManager(didReceive data: Data)

    func serialManager(didFail error: ASSerialError)
}
