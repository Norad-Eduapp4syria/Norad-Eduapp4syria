﻿/* --------------------------------------------------------------
*   Indie Contruction : Modular Framework for Unity
*   Copyright(c) 2016 Indie Construction / Paolo Bragonzi
*   All rights reserved. 
*   For any information refer to http://www.indieconstruction.com
*   
*   This library is free software; you can redistribute it and/or
*   modify it under the terms of the GNU Lesser General Public
*   License as published by the Free Software Foundation; either
*   version 3.0 of the License, or(at your option) any later version.
*   
*   This library is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
*   Lesser General Public License for more details.
*   
*   You should have received a copy of the GNU Lesser General Public
*   License along with this library.
* -------------------------------------------------------------- */
using UnityEngine;
using System;
using System.Collections.Generic;
using ModularFramework.Core;

namespace ModularFramework.Modules
{
    /// <summary>
    /// Concrete implementation for module type PlayerProfileModule.
    /// </summary>
    public class PlayerProfileModuleDefault : IPlayerProfileModule
    {
        public IPlayerProfile ActivePlayer { get; set; }

        #region IModule Implementation
        public IPlayerProfileModule ConcreteModuleImplementation { get; set; }
        private GlobalOptions options;
        public GlobalOptions Options {
            get { return options; }
            set {
                if(value != options) { 
                    options = value;
                    // Auto save at any change
                    SaveAllOptions();
                } else { 
                    options = value;
                }
            }
        }

        public IModuleSettings Settings { get; set; }

        public IPlayerProfileModule SetupModule(IPlayerProfileModule _concreteModule, IModuleSettings _settings = null)
        {
            Settings = _settings;
            // Add Here setup stuffs for this concrete implementation
            return this;
        }
        #endregion

        /// <summary>
        /// Create new player profile, if not exist already, and save updated list of available players on PlayerPrefs.
        /// </summary>
        /// <param name="_newPlayer"></param>
        /// <param name="_extProfile"></param>
        /// <returns></returns>
        public IPlayerProfile CreateNewPlayer(IPlayerProfile _newPlayer, IPlayerExtendedProfile _extProfile = null) {
            if (!Options.AvailablePlayers.Exists(p => p == _newPlayer.Key)) {
                Options.AvailablePlayers.Add(_newPlayer.Key);
                SavePlayerSettings(_newPlayer);
                SaveAllOptions();
            }
            return _newPlayer;
        }

        /// <summary>
        /// Delete player.
        /// </summary>
        /// <param name="_playerId"></param>
        public void DeletePlayer(string _playerId) {
            PlayerPrefs.DeleteKey(GetStoreKeyForPlayer(_playerId));
            Options.AvailablePlayers.Remove(_playerId);
        }

        /// <summary>
        /// Load player settings.
        /// </summary>
        /// <param name="_playerId"></param>
        public IPlayerProfile LoadPlayerSettings<T>(string _playerId) where T : IPlayerProfile {
            if (PlayerPrefs.HasKey(GetStoreKeyForPlayer(_playerId))) {
                string serializableProfile = PlayerPrefs.GetString(GetStoreKeyForPlayer(_playerId));
                IPlayerProfile returnProfile = JsonUtility.FromJson<T>(serializableProfile);
                returnProfile.Key = _playerId;
                return returnProfile;
            } else {
                Debug.LogFormat("Profile {0} not found.", _playerId);
            }
            return null;
        }

        /// <summary>
        /// Save player settings on PlayerPrefs (do not update list of players and global options).
        /// </summary>
        /// <param name="_newPlayer"></param>
        /// <param name="_extProfile"></param>
        public void SavePlayerSettings(IPlayerProfile _newPlayer, IPlayerExtendedProfile _extProfile = null)
        {
            string storeKey = GetStoreKeyForPlayer(_newPlayer.Key);
            string serializedObjs = JsonUtility.ToJson(_newPlayer);
            if (serializedObjs != null)
                PlayerPrefs.SetString(storeKey, serializedObjs);
            else
                Debug.Log("Unable to serialize player profile : " + _newPlayer.Key);
            PlayerPrefs.Save();
        }

        /// <summary>
        /// Set the active player.
        /// </summary>
        /// <param name="_playerId"></param>
        public void SetActivePlayer<T>(string _playerId) where T : IPlayerProfile {
            if (!Options.AvailablePlayers.Exists(p => p == _playerId)) // If player is not in active players list...
                return;
            IPlayerProfile pp = LoadPlayerSettings<T>(_playerId);
            if (pp == null) {
                Debug.LogError("Player not found");
            } else {
                ActivePlayer = pp;
            }
        }

        /// <summary>
        /// Update player settings (and if, extended profile).
        /// </summary>
        /// <param name="_newPlayer"></param>
        /// <param name="_extProfile"></param>
        /// <returns></returns>
        public IPlayerProfile UpdatePlayer(IPlayerProfile _newPlayer, IPlayerExtendedProfile _extProfile = null)
        {
            SavePlayerSettings(_newPlayer);
            return _newPlayer;
        }

        ///// <summary>
        ///// Loads the global options.
        ///// </summary>
        ///// <returns></returns>
        //public IGlobalOptions LoadGlobalOptions<T>() where T : IGlobalOptions {
        //    return LoadGlobalOptions<T>(Activator.CreateInstance<T>());
        //}

        /// <summary>
        /// Loads the global options with default fallback value.
        /// </summary>
        /// <typeparam name="T"></typeparam>
        /// <param name="_defaultOptions">The default options.</param>
        /// <returns></returns>
        public GlobalOptions LoadGlobalOptions<T>(T _defaultOptions) where T : GlobalOptions {
            string serializedObjs;
            if (PlayerPrefs.HasKey(OPTIONS_PREFS_KEY)) {
                serializedObjs = PlayerPrefs.GetString(OPTIONS_PREFS_KEY);
                Options = JsonUtility.FromJson<T>(serializedObjs);
                return options;
            } else {
                // Players list not created yet.
                Options = _defaultOptions;
                LoadGlobalOptions<T>(_defaultOptions);
                SaveAllOptions();
                return _defaultOptions;
            }
        }

        /// <summary>
        /// Save all player profiles.
        /// </summary>
        public void SaveAllOptions() {
            string serializedObjs = JsonUtility.ToJson(Options);
            PlayerPrefs.SetString(OPTIONS_PREFS_KEY, serializedObjs);
            PlayerPrefs.Save();
        }

        #region Data Store
        const string OPTIONS_PREFS_KEY = "OPTIONS";
        const string PLAYER_PREFS_KEY = "PLAYER";

        /// <summary>
        /// Return correct player pref key.
        /// </summary>
        /// <param name="_playerId"></param>
        /// <returns></returns>
        static string GetStoreKeyForPlayer(string _playerId)
        {
            return string.Format("{0}_{1}", PLAYER_PREFS_KEY, _playerId);
        }
        #endregion
    }
}
