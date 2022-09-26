import { createStore } from 'vuex'
import axios from 'axios'

export default createStore({
    state: {
        allData: [], singleData: {}, currentData: {}
    }, getters: {}, mutations: {
        getAllData(state, result) {
            state.allData = result
        }, getSingleData(state, result) {
            state.singleData = result
            state.allData.unshift(result) //添加到数组的第一位
        }, getCurrentData(state, filename) {
            axios.get("http://localhost:8000/heart/single_fileinfo?filepath=./static/audio_data/" + filename).then(response => {
                state.currentData = response.data[0].fields
            }).catch(error => {
                console.log(error);
            });
        }
    }, actions: {
        getAllData(context) {
            axios.get("http://localhost:8000/heart/all_fileinfo").then(response => {
                let tmp = []
                for (let i = 0; i < response.data.length; i++) {
                    tmp.push(response.data[i].fields);
                }
                tmp = tmp.reverse();
                context.commit('getAllData', tmp)
                context.commit('getCurrentData', tmp[0].filename)
            }).catch(error => {
                console.log(error);
            });
        }, getSingleData(context, filename) {
            axios.get("http://localhost:8000/heart/fileinfo?filename=" + filename).then(response => {
                context.commit('getSingleData', response.data.fields)
            }).catch(error => {
                console.log(error);
            });
        }
    }, modules: {}
})
