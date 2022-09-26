<template>
  <div>
    <div>
      <FileInfo></FileInfo>
    </div>
    <div>
      <FileFigure4></FileFigure4>
    </div>
    <div>
      <FileUpload></FileUpload>
    </div>
    <div><FileList></FileList></div>
  </div>
</template>

<script lang="ts">
import { Options, Vue } from "vue-class-component";
import FileFigure4 from "@/components/FileFigure4.vue";
import FileInfo from "@/components/FileInfo.vue";
import FileUpload from "@/components/FileUpload.vue";
import FileList from "@/components/FileList.vue";

@Options({
  components: {
    FileInfo,
    FileUpload,
    FileFigure4,
    FileList,
  },
})
export default class HomeView extends Vue {}
</script>
